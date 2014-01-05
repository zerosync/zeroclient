#include "zsindex.h"

ZSIndex::ZSIndex(QObject *parent, ZSDatabase *zsdatabase) :
    QObject(parent)
{
    database = zsdatabase;
    latestState = database->getLatestState();
}


void ZSIndex::slotUpdateIndex()
{
    latestState = database->getLatestState();
    QSqlQuery *query = database->fetchAllChangedEntries();
    if(query == NULL)
    {
        qDebug("Error - ZSIndex::slotUpdateIndex() failed: QSqlQuery object \"query\" is NULL");
        return;
    }
    query->last();
    query->first();
    query->previous();
    while(query->next())
    {
        QString newPath = query->value(4).toString();
        int updated = query->value(6).toInt();
        int renamed = query->value(7).toInt();
        int deleted = query->value(8).toInt();

        if(updated == 1)
        {
            database->insertNewIndexEntry(latestState + 1, query->value(0).toString(), "UPD", query->value(1).toLongLong(), query->value(3).toInt(), QString(), query->value(2).toString());
        }
        if(deleted == 1)
        {
            database->insertNewIndexEntry(latestState + 1, query->value(0).toString(), "DEL", query->value(1).toLongLong(), query->value(3).toInt(), QString(), query->value(2).toString());
        }
        if(renamed == 1)
        {
            database->insertNewIndexEntry(latestState + 1, query->value(0).toString(), "REN", query->value(1).toLongLong(), query->value(3).toInt(), newPath, query->value(2).toString());
        }

    }
    database->resetFileMetaData();
    qDebug() << "Information - ZSIndex::slotUpdateIndex() succeeded: Fileindex updated";
}

