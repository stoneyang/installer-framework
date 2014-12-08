/**************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Installer Framework.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights. These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
**
** $QT_END_LICENSE$
**
**************************************************************************/

#include "systeminfo.h"
#include <QSysInfo>

namespace QInstaller {

/*!
    \qmltype systemInfo
    \inqmlmodule scripting

    \brief Provides information about the operating system.
*/


SystemInfo::SystemInfo(QObject *parent) : QObject(parent)
{
}


/*!
    \qmlproperty string systemInfo::currentCpuArchitecture

    The architecture of the CPU that the application is running on, in text format.

    Possible values include
    \list
        \li "i386"
        \li "x86_64"
    \endlist

    Note that this function depends on what the OS will report and may not detect the actual CPU
    architecture if the OS hides that information or is unable to provide it. For example, a 32-bit
    OS running on a 64-bit CPU is usually unable to determine whether the CPU is actually capable
    of running 64-bit programs.

    \sa QSysInfo::currentCpuArchitecture()
*/
QString SystemInfo::currentCpuArchitecture() const
{
    return QSysInfo::currentCpuArchitecture();
}

/*!
    \qmlproperty string systemInfo::kernelType

    The type of the operating system kernel the installer was compiled for. It is also the
    kernel the installer is running on, unless the host operating system is running a form of
    compatibility or virtualization layer.

    For Windows, Linux, and OS X this will return
    \list
        \li "winnt"
        \li "linux"
        \li "darwin"
    \endlist

    On Unix systems, it returns the same as the output of \c {uname -s} (lowercased).

    \sa QSysInfo::kernelType()
*/
QString SystemInfo::kernelType() const
{
    return QSysInfo::kernelType();
}

/*!
    \qmlproperty string systemInfo::kernelVersion

    Example values are

    \list
        \li "6.1.7601" for Windows 7 with Service Pack 1
        \li "3.16.6-2-desktop" for openSUSE 13.2 kernel 3.16.6-2
        \li "12.5.0" last release of OS X "Mountain Lion"
    \endlist

    The release version of the operating system kernel. On Windows, it returns the version of the
    NT or CE kernel. On Unix systems, including OS X, it returns the same as the \c {uname -r}
    command would return.

    \sa QSysInfo::kernelVersion()
*/
QString SystemInfo::kernelVersion() const
{
    return QSysInfo::kernelVersion();
}

/*!
    \qmlproperty string systemInfo::productType

    The product name of the operating system this application is running in.

    Example values are

    \list
        \li "windows"
        \li "opensuse" (for the Linux openSUSE distribution)
        \li "osx"
    \endlist

    \sa QSysInfo::productType()
*/
QString SystemInfo::productType() const
{
    return QSysInfo::productType();
}

/*!
    \qmlproperty string systemInfo::productVersion

    The product version of the operating system in string form. If the version could not be
    determined, this function returns "unknown".

    Example values are

    \list
        \li "7" for Windows 7
        \li "13.2" for openSUSE 13.2
        \li "10.8" for OS X Mountain Lion
    \endlist

    \sa QSysInfo::productVersion()
*/
QString SystemInfo::productVersion() const
{
    return QSysInfo::productVersion();
}

/*!
    \qmlproperty string systemInfo::prettyProductName

    A prettier form of systemInfo::productType and systemInfo::productVersion, containing other
    tokens like the operating system type, codenames and other information. The result of this
    function is suitable for displaying to the user.

    Example values are

    \list
        \li "Windows 7"
        \li "openSUSE 13.2 (Harlequin) (x86_64)"
        \li "OS X Mountain Lion (10.8)"
    \endlist


    \sa QSysInfo::prettyProductName()
*/
QString SystemInfo::prettyProductName() const
{
    return QSysInfo::prettyProductName();
}

} // namespace QInstaller