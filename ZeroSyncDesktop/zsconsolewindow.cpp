/* =========================================================================
   ZSConsoleWindow - Class that is used to start ZeroSync as console app


   -------------------------------------------------------------------------
   Copyright (c) 2014 Kevin Sapper, Tommy Bluhm
   Copyright other contributors as noted in the AUTHORS file.

   This file is part of ZeroSync, see http://zerosync.org.

   This is free software; you can redistribute it and/or modify it under
   the terms of the GNU Lesser General Public License as published by the
   Free Software Foundation; either version 3 of the License, or (at your
   option) any later version.
   This software is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTA-
   BILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General
   Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program. If not, see http://www.gnu.org/licenses/.
   =========================================================================
*/

#include "zsconsolewindow.h"

ZSConsoleWindow::ZSConsoleWindow(QObject *parent, bool newDirectory) :
    QObject(parent)
{
    if(newDirectory)
    {
        ZSDatabase::getInstance()->deleteAllRowsFromFilesTable();
        ZSDatabase::getInstance()->setZeroSyncFolderChangedFlagToFileIndexTable();
    }

    fileSystemWatcher = new ZSFileSystemWatcher();
    fileSystemWatcher->setZeroSyncDirectory(ZSSettings::getInstance()->getZeroSyncDirectory());
    index = new ZSIndex();
    connector = new ZSConnector();
    htmlBuilder = new ZShtmlBuilder();

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), index, SLOT(slotUpdateIndex()));

    if(ZSSettings::getInstance()->getSyncInterval() > 0)
    {
        index->slotUpdateIndex();
        timer->start(ZSSettings::getInstance()->getSyncInterval());
    }

    QDir directoryOfIndexFile("");
    directoryOfIndexFile.mkpath(QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0));
}

