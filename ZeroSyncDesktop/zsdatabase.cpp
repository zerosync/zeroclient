#include "zsdatabase.h"

ZSDatabase::ZSDatabase(QObject *parent) :
    QObject(parent)
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(getDataBasePath());
    database.open();
    if(!tablesCreated())
    {
        createTables();
    }
}


QString ZSDatabase::getDataBasePath()
{
    return QString(QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0) + "/zsdatabase.sqlite");
}


void ZSDatabase::createTables()
{
    QFile fileCreateTableFiles(":/sql/resources/sql/create_files.sql");
    QFile fileCreateTableIndex(":/sql/resources/sql/create_index.sql");

    if(!fileCreateTableFiles.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error: Can't open resource file :sql/create_files.sql";
    }

    if(!fileCreateTableIndex.open(QIODevice::ReadOnly))
    {
        qDebug() << "Error: Can't open resource file :sql/create_index.sql";
    }

    if(database.open())
    {
        QString databaseQuery;
        QSqlQuery query(database);
        QTextStream inputStream(&fileCreateTableFiles);
        databaseQuery = inputStream.readAll();
        fileCreateTableFiles.close();
        if(!query.exec(databaseQuery))
        {
            qDebug() << "Error: Can't execute database query from \":sql/create_files.sql\"";
        }
    }

    if(database.open())
    {
        QString databaseQuery;
        QSqlQuery query(database);
        QTextStream inputStream(&fileCreateTableIndex);
        databaseQuery = inputStream.readAll();
        fileCreateTableIndex.close();
        if(!query.exec(databaseQuery))
        {
            qDebug() << "Error: Can't execute database query from \":sql/create_index.sql\"";
        }
    }
}


bool ZSDatabase::tablesCreated()
{
    QFile database(getDataBasePath());
    if(database.size() == 0)
    {
        database.remove();
        return false;
    }
    return true;
}


void ZSDatabase::insertNewFile(QString path, qint64 timestamp, QString checksum, qint64 size)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("INSERT INTO files (path, timestamp, checksum, size, newpath, changed, updated, renamed, deleted) VALUES (:path, :timestamp, :checksum, :size, :newpath, :changed, :updated, :renamed, :deleted)");
        query.bindValue(":path", path);
        query.bindValue(":timestamp", timestamp);
        query.bindValue(":checksum", checksum);
        query.bindValue(":size", size);
        query.bindValue(":newpath", QString());
        query.bindValue(":changed", 1);
        query.bindValue(":updated", 1);
        query.bindValue(":renamed", 0);
        query.bindValue(":deleted", 0);
        if(!query.exec())
        {
//            qDebug() << "Error: Can't execute database query to insert a file into the database";
        }
    }
}


void ZSDatabase::setFileChanged(QString path, int value)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("UPDATE files SET changed = :value WHERE path = :path");
        query.bindValue(":value", value);
        query.bindValue(":path", path);
        if(!query.exec())
        {
            qDebug() << "Error: Can't execute database query to change the attribute \"changed\"";
        }
    }
}


void ZSDatabase::setFileUpdated(QString path, int value)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("UPDATE files SET updated = :value WHERE path = :path");
        query.bindValue(":value", value);
        query.bindValue(":path", path);
        if(!query.exec())
        {
            qDebug() << "Error: Can't execute database query to change the attribute \"updated\"";
        }
    }
}


void ZSDatabase::setFileRenamed(QString path, int value)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("UPDATE files SET renamed = :value WHERE path = :path");
        query.bindValue(":value", value);
        query.bindValue(":path", path);
        if(!query.exec())
        {
            qDebug() << "Error: Can't execute database query to change the attribute \"renamed\"";
        }
    }
}


void ZSDatabase::setFileDeleted(QString path, int value)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("UPDATE files SET deleted = :value WHERE path = :path");
        query.bindValue(":value", value);
        query.bindValue(":path", path);
        if(!query.exec())
        {
            qDebug() << "Error: Can't execute database query to change the attribute \"deleted\"";
        }
    }
}

void ZSDatabase::setFileHashToZero(QString path)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("UPDATE files SET checksum = 0 WHERE path = :path");
        query.bindValue(":path", path);
        if(!query.exec())
        {
            qDebug() << "Error: Can't execute database query to change set file checksum to zero";
        }
    }
}

void ZSDatabase::setNewPath(QString path, QString newPath)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("UPDATE files SET newpath = :newPath WHERE path = :path");
        query.bindValue(":newPath", newPath);
        query.bindValue(":path", path);
        if(!query.exec())
        {
            qDebug() << "Error: Can't execute database query to change the attribute \"newpath\"";
        }
    }
}

bool ZSDatabase::isFileChanged(QString path)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("SELECT * FROM files WHERE path = :path AND changed = 1");
        query.bindValue(":path", path);
        if(!query.exec())
        {
            qDebug() << "ZSDatabase:Error: Can't execute database query to detect if file is changed";
            return false;
        }
        if(query.next())
        {
            return true;
        }
        return false;
    }
    return false;
}

bool ZSDatabase::isFileUpdated(QString path)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("SELECT * FROM files WHERE path = :path AND updated = 1");
        query.bindValue(":path", path);
        if(!query.exec())
        {
            qDebug() << "ZSDatabase:Error: Can't execute database query to detect if file is updated";
            return false;
        }
        if(query.next())
        {
            return true;
        }
        return false;
    }
    return false;
}

bool ZSDatabase::isFileRenamed(QString path)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("SELECT * FROM files WHERE path = :path AND renamed = 1");
        query.bindValue(":path", path);
        if(!query.exec())
        {
            qDebug() << "ZSDatabase:Error: Can't execute database query to detect if file is renamed";
            return false;
        }
        if(query.next())
        {
            return true;
        }
        return false;
    }
    return false;
}

bool ZSDatabase::isFileDeleted(QString path)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("SELECT * FROM files WHERE path = :path AND deleted = 1");
        query.bindValue(":path", path);
        if(!query.exec())
        {
            qDebug() << "ZSDatabase:Error: Can't execute database query to detect if file is deleted!";
            return false;
        }
        if(query.next())
        {
            return true;
        }
        return false;
    }
    return false;
}

QString ZSDatabase::getFilePathForHash(QString hash)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("SELECT * FROM files WHERE checksum = :checksum");
        query.bindValue(":checksum", hash);
        if(!query.exec())
        {
            qDebug() << "ZSDatabase:Error: Can't execute database query to get filepath for hash";
            return QString();
        }
        if(query.next())
        {
            return query.value(0).toString();
        }
        return QString();
    }
    return QString();
}


void ZSDatabase::setFileMetaData(QString path, qint64 timestamp, QString checksum, qint64 size)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("UPDATE files SET timestamp = :timestamp, checksum = :checksum,  size = :size WHERE path = :path");
        query.bindValue(":path", path);
        query.bindValue(":timestamp", timestamp);
        query.bindValue(":checksum", checksum);
        query.bindValue(":size", size);
        if(!query.exec())
        {
            qDebug() << "Error: Can't execute database query to set file meta data";
        }
    }
}


bool ZSDatabase::existsFileEntry(QString path)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("SELECT * FROM files WHERE path = :path");
        query.bindValue(":path", path);
        if(!query.exec())
        {
            qDebug() << "Error: Can't execute database query to check if file entry exists";
            return false;
        }
        if(query.next())
        {
            return true;
        }
        return false;
    }
    return false;
}

bool ZSDatabase::existsFileHash(QString checksum)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("SELECT * FROM files WHERE checksum = :checksum");
        query.bindValue(":checksum", checksum);
        if(!query.exec())
        {
            qDebug() << "Error: Can't execute database query to check if file hash already exists";
            return false;
        }
        if(query.next())
        {
            return true;
        }
        return false;
    }
    return false;
}


QSqlQuery* ZSDatabase::fetchAllChangedEntries()
{
    QSqlQuery *query = new QSqlQuery(database);
    if(database.open())
    {
        query->prepare("SELECT * FROM files WHERE changed = 1");
        if(!query->exec())
        {
            qDebug() << "Error: Can't execute database query to fetch all changed files";
            return NULL;
        }
        else
        {
            return query;
        }
    }
    return NULL;
}


void ZSDatabase::insertNewIndexEntry(int state, QString path, QString operation, qint64 timestamp, qint64 size, QString newpath, QString checksum)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("INSERT INTO fileindex (state, path, operation, timestamp, size, newpath, checksum) VALUES (:state, :path, :operation, :timestamp, :size, :newpath, :checksum)");
        query.bindValue(":state", state);
        query.bindValue(":path", path);
        query.bindValue(":operation", operation);
        query.bindValue(":timestamp", timestamp);
        query.bindValue(":size", size);
        query.bindValue(":newpath", newpath);
        query.bindValue(":checksum", checksum);
        if(!query.exec())
        {
//            qDebug() << "Error: Can't execute database query to insert a new index entry into the database";
        }
    }
}

int ZSDatabase::getLatestState()
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("SELECT MAX(state) FROM fileindex");
        if(!query.exec())
        {
            qDebug() << "Error: Can't execute database query to get latest state";
            return -1;
        }
        if(query.next())
        {
            return query.value(0).toInt();
        }
        return 0;
    }
    return -1;
}

void ZSDatabase::resetFileMetaData()
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("UPDATE files SET changed = 0, updated = 0 WHERE changed = 1");
        if(!query.exec())
        {
            qDebug() << "Error: Can't execute database query to reset file meta data";
        }
    }
}

