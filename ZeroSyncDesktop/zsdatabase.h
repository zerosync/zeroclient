/* =========================================================================
   ZSDatabase - Database class of ZeroSync desktop client


   -------------------------------------------------------------------------
   Copyright (c) 2014 Tommy Bluhm
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
#include <QDir>
#include <QSqlQuery>
#include <QTextStream>
#include <QtDebug>
#include <QSqlError>
#include <QMutex>


//!  Class that provides the ZeroSync local database functionality
/*!
  This class provides an interface to the local SQLite database, that is used
  to save the current ZeroSync folder status and the file index, that is used to
  synchronize files between clients.
*/
class ZSDatabase : public QObject
{
    Q_OBJECT

public:
    //!  GetInstance-Function
    /*!
      Static function that implements the Singleton functionality.
    */
    static ZSDatabase* getInstance()
    {
        static QMutex mutex;
        if (!m_Instance)
        {
            mutex.lock();
            if (!m_Instance)
            {
                m_Instance = new ZSDatabase();
            }
            mutex.unlock();
        }
        return m_Instance;
    }

    static void deleteInstance()
    {
        static QMutex mutex;
        mutex.lock();
        delete m_Instance;
        m_Instance = 0;
        mutex.unlock();
    }
//    explicit ZSDatabase(QObject *parent = 0);
    void insertNewFile(QString, qint64, QString, qint64);
    void setFileMetaData(QString, qint64, QString, qint64);
    void setFileChanged(QString, int);
    void setFileUpdated(QString, int);
    void setFileRenamed(QString, int);
    void setFileReference(QString, quint32);
    void setFileDeleted(QString, int);
    void setFileTimestamp(QString, qint64);
    void setFileChangedSelf(QString, int);
    void setNewPath(QString, QString);
    QString getFilePathForHash(QString);
    void setFileHashToZero(QString);
    bool isFileChanged(QString);
    bool isFileChangedSelf(QString);
    bool isFileUpdated(QString);
    bool isFileRenamed(QString);
    bool isFileDeleted(QString);
    bool existsFileEntry(QString);
    bool existsFileHash(QString);
    QSqlQuery fetchAllChangedEntriesInFilesTable();
    QSqlQuery fetchAllEntriesInFilesTable();
    QSqlQuery fetchAllUndeletedEntries();
    QSqlQuery fetchFileByPath(QString path);
    QSqlQuery fetchUpdate(int);
    QSqlQuery fetchUpdateFromState(int fromState);
    void insertNewIndexEntry(int, QString, QString, qint64, qint64, QString, QString, int);
    int getLatestState();
    void resetFileMetaData();
    void deleteAllRowsFromFilesTable();
    void setZeroSyncFolderChangedFlagToFileIndexTable();
    qint64 getTimestampForFile(QString);

private:
    //!  "Disabled" Constructor
    /*!
      Constructor that is set to private to implement the Singleton functionality.
    */
    ZSDatabase();

    //!  "Disabled" Constructor
    /*!
      Constructor that is set to private to implement the Singleton functionality.
    */
    ZSDatabase(const ZSDatabase &);

    //!  "Disabled" Operator
    /*!
      Operator that is set to private to implement the Singleton functionality.
    */
    ZSDatabase& operator=(const ZSDatabase &);

    //!  ZDatabase Singleton Instance
    /*!
      Instance that can be requested with the getInstance-Method.
    */
    static ZSDatabase* m_Instance;



    QSqlDatabase database;
    QString getDataBasePath();
    void createTables();
    bool tablesCreated();

signals:

public slots:

};

#endif // ZSDATABASE_H
