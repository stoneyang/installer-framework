/**************************************************************************
**
** This file is part of Qt SDK**
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).*
**
** Contact:  Nokia Corporation qt-info@nokia.com**
**
** No Commercial Usage
**
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception version
** 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you are unsure which license is appropriate for your use, please contact
** (qt-info@nokia.com).
**
**************************************************************************/
#ifndef QINSTALLER_P_H
#define QINSTALLER_P_H

#include "common/installersettings.h"

#include <KDToolsCore/KDSysInfo>

#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtCore/QPair>
#include <QtCore/QPointer>
#include <QtCore/QVector>

class FSEngineClientHandler;
QT_FORWARD_DECLARE_CLASS(QFile)
QT_FORWARD_DECLARE_CLASS(QFileInfo)

namespace KDUpdater {
    class Application;
    class UpdateOperation;
}

namespace QInstaller {

struct BinaryLayout;

class Component;
class Installer;
class TempDirDeleter;

class InstallerPrivate : public QObject
{
    Q_OBJECT;
    friend class Installer;

public:
    enum OperationType {
        Backup,
        Perform,
        Undo
    };

    InstallerPrivate();
    explicit InstallerPrivate(Installer *q, qint64 magicInstallerMaker,
        const QVector<KDUpdater::UpdateOperation*> &performedOperations);
    ~InstallerPrivate();

    static bool isProcessRunning(const QString &name,
        const QList<KDSysInfo::ProcessInfo> &processes);

    static bool performOperationThreaded(KDUpdater::UpdateOperation *op,
        InstallerPrivate::OperationType type = InstallerPrivate::Perform);

    void initialize();

    void setStatus(int status);
    bool statusCanceledOrFailed() const;

    QString targetDir() const;
    QString registerPath() const;

    QString uninstallerName() const;
    QString installerBinaryPath() const;
    void readUninstallerIniFile(const QString &targetDir);
    void writeUninstaller(QVector<KDUpdater::UpdateOperation*> performedOperations);

    QString configurationFileName() const;
    QString componentsXmlPath() const;
    QString localComponentsXmlPath() const;

    Installer *installer() const { return q; }

    void runInstaller();
    bool isInstaller() const;

    void runUninstaller();
    bool isUninstaller() const;

    void runUpdater();
    bool isUpdater() const;

    void runPackageUpdater();
    bool isPackageManager() const;

    QString replaceVariables(const QString &str) const;
    QByteArray replaceVariables(const QByteArray &str) const;

    KDUpdater::UpdateOperation* createOwnedOperation(const QString &type);
    void stopProcessesForUpdates(const QList<Component*> &components);
    int countProgressOperations(const QList<Component*> &components);
    int countProgressOperations(const QList<KDUpdater::UpdateOperation*> &operations);
    void connectOperationToInstaller(KDUpdater::UpdateOperation* const operation,
        double progressOperationPartSize);

    KDUpdater::UpdateOperation* createPathOperation(const QFileInfo &fileInfo,
        const QString &componentName);
    void registerPathesForUninstallation(const QList<QPair<QString, bool> > &pathesForUninstallation,
        const QString &componentName);

    void addPerformed(KDUpdater::UpdateOperation* op) {
        m_performedOperationsCurrentSession.push_back(op);
    }

    void commitSessionOperations() {
        m_performedOperationsOld += m_performedOperationsCurrentSession;
        m_performedOperationsCurrentSession.clear();
    }

    void installComponent(Component *component, double progressOperationSize, bool adminRightsGained = false);

signals:
    void installationStarted();
    void installationFinished();
    void uninstallationStarted();
    void uninstallationFinished();

public:
    KDUpdater::Application *m_app;
    TempDirDeleter *m_tempDirDeleter;
    FSEngineClientHandler *m_FSEngineClientHandler;

    int m_status;
    bool m_forceRestart;
    int m_silentRetries;
    bool m_testChecksum;
    bool m_launchedAsRoot;
    bool m_completeUninstall;
    bool m_needToWriteUninstaller;
    QHash<QString, QString> m_vars;
    QHash<QString, bool> m_sharedFlags;
    InstallerSettings m_installerSettings;
    QString m_installerBaseBinaryUnreplaced;

    qint64 m_globalDictOffset;

    qint64 m_componentsCount;
    qint64 m_firstComponentStart;
    qint64 m_componentOffsetTableStart;

    qint64 m_componentsDictCount;
    qint64 m_firstComponentDictStart;
    qint64 m_componentDictOffsetTableStart;

    QList<Component*> m_rootComponents;
    QList<Component*> m_updaterComponents;
    QList<Component*> m_updaterComponentsDeps;

    QList<KDUpdater::UpdateOperation*> ownedOperations;
    QVector<KDUpdater::UpdateOperation*> m_performedOperationsOld;
    QVector<KDUpdater::UpdateOperation*> m_performedOperationsCurrentSession;

private:
    void deleteUninstaller();
    void registerUninstaller();
    void unregisterUninstaller();

    void writeUninstallerBinary(QFile *const input, qint64 size);
    void writeUninstallerBinaryData(QIODevice *output, QFile *const input,
        const QVector<KDUpdater::UpdateOperation*> &performedOperations, const BinaryLayout &layout);

    void runUndoOperations(const QList<KDUpdater::UpdateOperation*> &undoOperations,
        double undoOperationProgressSize, bool adminRightsGained, bool deleteOperation);

private:
    Installer *q;
    qint64 m_magicBinaryMarker;
};

}   // QInstaller

#endif  // QINSTALLER_P_H
