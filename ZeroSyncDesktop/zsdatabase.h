/* =========================================================================
   ZSDatabase - Database class of ZeroSync desktop client


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


#ifndef ZSDATABASE_H
#define ZSDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QStandardPaths>
#include <QFile>
#include <QSqlQuery>
#include <QTextStream>
#include <QtDebug>
#include <QSqlError>

class ZSDatabase : public QObject
{
    Q_OBJECT

public:
    explicit ZSDatabase(QObject *parent = 0);
    void insertNewFile(QString, qint64, QString, qint64);
    void setFileMetaData(QString, qint64, QString, qint64);
    void setFileChanged(QString, int);
    void setFileUpdated(QString, int);
    void setFileRenamed(QString, int);
    void setFileDeleted(QString, int);
    void setNewPath(QString, QString);
    QString getFilePathForHash(QString);
    void setFileHashToZero(QString);
    bool isFileChanged(QString);
    bool isFileUpdated(QString);
    bool isFileRenamed(QString);
    bool isFileDeleted(QString);
    bool existsFileEntry(QString);
    bool existsFileHash(QString);
    QSqlQuery* fetchAllChangedEntries();
    void insertNewIndexEntry(int, QString, QString, qint64, qint64, QString, QString);
    int getLatestState();
    void resetFileMetaData();
    void deleteAllRowsFromFilesTable();
    void setZeroSyncFolderChangedFlagToFileIndexTable();
    qint64 getTimestampForFile(QString);

private:
    QSqlDatabase database;

    QString getDataBasePath();
    void createTables();
    bool tablesCreated();

signals:

public slots:

};

#endif // ZSDATABASE_H
