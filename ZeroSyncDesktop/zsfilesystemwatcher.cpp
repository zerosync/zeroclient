/* =========================================================================
   ZSFileSystemWatcher - Filesystem monitoring class for the ZeroSync client


   -------------------------------------------------------------------------
   Copyright (c) 2013 Tommy Bluhm
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


#include "zsfilesystemwatcher.h"


ZSFileSystemWatcher::ZSFileSystemWatcher(QObject *parent) :
    QObject(parent),
    pathToZeroSyncDirectory()
{
    fileSystemWatcher = new QFileSystemWatcher();
    establishConnections();
}


void ZSFileSystemWatcher::establishConnections()
{
    connect(fileSystemWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(slotDirectoryChanged(QString)));
    connect(fileSystemWatcher, SIGNAL(fileChanged(QString)), this, SLOT(slotFileChanged(QString)));
}


void ZSFileSystemWatcher::setZeroSyncDirectory(QString pathToDirectory)
{
    pathToZeroSyncDirectory = pathToDirectory;
    setFilesToWatch(pathToZeroSyncDirectory);
}

void ZSFileSystemWatcher::changeZeroSyncDirectory(QString pathToDirectory)
{
    pathToZeroSyncDirectory = pathToDirectory;
    fileSystemWatcher->removePaths(fileSystemWatcher->files());
    fileSystemWatcher->removePaths(fileSystemWatcher->directories());
    ZSDatabase::getInstance()->deleteAllRowsFromFilesTable();
    ZSDatabase::getInstance()->setZeroSyncFolderChangedFlagToFileIndexTable();
    setFilesToWatch(pathToZeroSyncDirectory);
}


void ZSFileSystemWatcher::setFilesToWatch(QString path)
{
    fileSystemWatcher->addPath(path);
    QDirIterator directoryIterator(path,  QDir::Files| QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while(directoryIterator.hasNext())
    {
        directoryIterator.next();
        fileSystemWatcher->addPath(directoryIterator.filePath());
        if(directoryIterator.fileInfo().isFile())
        {
            ZSFileMetaData fileMetaData(this, directoryIterator.filePath(), pathToZeroSyncDirectory);
            if(!ZSDatabase::getInstance()->existsFileEntry(fileMetaData.getFilePath()))
            {
                if(fileMetaData.getFileSize() > 0)
                {
                    if(ZSDatabase::getInstance()->existsFileHash(fileMetaData.getHash()))
                    {
                        if(!fileMetaData.existsFile(pathToZeroSyncDirectory + "/" + ZSDatabase::getInstance()->getFilePathForHash(fileMetaData.getHash())))
                        {
                            if(fileMetaData.getLastModified() == ZSDatabase::getInstance()->getTimestampForFile(ZSDatabase::getInstance()->getFilePathForHash(fileMetaData.getHash())))
                            {
                                QString filePathFromHash = ZSDatabase::getInstance()->getFilePathForHash(fileMetaData.getHash());
                                ZSDatabase::getInstance()->setFileChanged(filePathFromHash, 1);
                                ZSDatabase::getInstance()->setFileUpdated(filePathFromHash, 0);
                                ZSDatabase::getInstance()->setFileRenamed(filePathFromHash, 1);
                                ZSDatabase::getInstance()->setFileChangedSelf(filePathFromHash, 0);
                                ZSDatabase::getInstance()->setFileHashToZero(filePathFromHash);
                                ZSDatabase::getInstance()->setNewPath(filePathFromHash, fileMetaData.getFilePath());
                                addFileToDatabase(directoryIterator.filePath());
                                continue;
                            }
                            else
                            {
                                addFileToDatabase(directoryIterator.filePath());
                                continue;
                            }
                        }
                        else
                        {
                            addFileToDatabase(directoryIterator.filePath());
                            continue;
                        }
                    }
                    else
                    {
                        addFileToDatabase(directoryIterator.filePath());
                        continue;
                    }
                }
            }
            else
            {
                if(fileMetaData.getLastModified() != ZSDatabase::getInstance()->getTimestampForFile(fileMetaData.getFilePath()))
                {
                    ZSDatabase::getInstance()->setFileChanged(fileMetaData.getFilePath(), 1);
                    ZSDatabase::getInstance()->setFileUpdated(fileMetaData.getFilePath(), 1);
                    ZSDatabase::getInstance()->setFileDeleted(fileMetaData.getFilePath(), 0);
                    ZSDatabase::getInstance()->setFileChangedSelf(fileMetaData.getFilePath(), 0);
                    ZSDatabase::getInstance()->setFileMetaData(fileMetaData.getFilePath(), fileMetaData.getLastModified(), fileMetaData.getHash(), fileMetaData.getFileSize());
                }
            }
        }
    }
    QSqlQuery query = ZSDatabase::getInstance()->fetchAllEntriesInFilesTable();

    query.last();
    query.first();
    query.previous();
    while(query.next())
    {
        ZSFileMetaData fileMetaData(this, pathToZeroSyncDirectory + "/" + query.value(0).toString(), pathToZeroSyncDirectory);
        if(!fileMetaData.existsFile(pathToZeroSyncDirectory + "/" + query.value(0).toString()) && !ZSDatabase::getInstance()->isFileRenamed(query.value(0).toString()))
        {
            ZSDatabase::getInstance()->setFileChanged(fileMetaData.getFilePath(), 1);
            ZSDatabase::getInstance()->setFileUpdated(fileMetaData.getFilePath(), 0);
            ZSDatabase::getInstance()->setFileDeleted(fileMetaData.getFilePath(), 1);
            ZSDatabase::getInstance()->setFileChangedSelf(fileMetaData.getFilePath(), 0);
            ZSDatabase::getInstance()->setFileMetaData(fileMetaData.getFilePath(), fileMetaData.getLastModified(), fileMetaData.getHash(), fileMetaData.getFileSize());
        }
    }
}


void ZSFileSystemWatcher::addFileToDatabase(QString pathToFile)
{
    ZSFileMetaData fileMetaData(this, pathToFile, pathToZeroSyncDirectory);
    ZSDatabase::getInstance()->insertNewFile(fileMetaData.getFilePath(), fileMetaData.getLastModified(), fileMetaData.getHash(), fileMetaData.getFileSize());
}


void ZSFileSystemWatcher::slotDirectoryChanged(QString pathToDirectory)
{
    emit signalDirectoryChangeRecognized(pathToDirectory);
    setFilesToWatch(pathToZeroSyncDirectory);
    qDebug() << "Information - ZSFileSystemWatcher::slotDirectoryChanged(): " << pathToDirectory;
}


void ZSFileSystemWatcher::slotFileChanged(QString pathToFile)
{
    ZSFileMetaData fileMetaData(this, pathToFile, pathToZeroSyncDirectory);
    emit signalFileChangeRecognized(fileMetaData.getFilePath());
    setFilesToWatch(pathToZeroSyncDirectory);
    qDebug() << "Information - ZSFileSystemWatcher::slotFileChanged(): " << fileMetaData.getFilePath();
}
