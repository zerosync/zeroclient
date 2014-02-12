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


#ifndef ZSFILESYSTEMWATCHER_H
#define ZSFILESYSTEMWATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QDir>
#include <QtDebug>
#include <QDirIterator>
#include <QCryptographicHash>
#include <QDateTime>
#include <QStandardPaths>
#include "zsdatabase.h"
#include "zsfilemetadata.h"
#include "zsindex.h"


//!  Class that provides the ZeroSync filesystem watcher
/*!
  This class provides the filewatcher functionality, that is used to
  store information about the ZeroSync folder in an local SQLite database.
*/
class ZSFileSystemWatcher : public QObject
{
    Q_OBJECT

public:
    explicit ZSFileSystemWatcher(QObject *parent = 0);
    void setZeroSyncDirectory(QString);
    void changeZeroSyncDirectory(QString);

private:
    QFileSystemWatcher *fileSystemWatcher;
    QString pathToZeroSyncDirectory;
    void establishConnections();
    void setFilesToWatch(QString);
    void addFileToDatabase(QString);

signals:
    void signalDirectoryChangeRecognized(QString);
    void signalFileChangeRecognized(QString);

private slots:
    void slotDirectoryChanged(QString);
    void slotFileChanged(QString);

};

#endif // ZSFILESYSTEMWATCHER_H
