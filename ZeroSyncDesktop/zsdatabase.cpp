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
        query.prepare("UPDATE files SET renamed = : WHERE path = :path");
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
            qDebug() << "Error: Can't execute database query to set file meta data";
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
            qDebug() << "Error: Can't execute database query to set file meta data";
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


void ZSDatabase::fetchAllChangedEntries(QSqlQuery *query)
{
    if(database.open())
    {
        query = new QSqlQuery(database);
        query->prepare("SELECT * FROM files WHERE changed = 1");
        if(!query->exec())
        {
            qDebug() << "Error: Can't execute database query to fetch all changed files";;
        }
    }
}


void ZSDatabase::insertNewIndexEntry(QString path, QString operation, qint64 timestamp, QString checksum, qint64 size)
{
    if(database.open())
    {
        QSqlQuery query(database);
        query.prepare("INSERT INTO index (path, operation, timestamp, size, newpath, checksum) VALUES (:path, :operation, :timestamp, :size, :newpath, :checksum)");
        query.bindValue(":path", path);
        query.bindValue(":operation", operation);
        query.bindValue(":timestamp", timestamp);
        query.bindValue(":size", size);
        query.bindValue(":newpath", QString());
        query.bindValue(":checksum", checksum);
        if(!query.exec())
        {
//            qDebug() << "Error: Can't execute database query to insert a new index entry into the database";
        }
    }
}
