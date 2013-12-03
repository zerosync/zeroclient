#include "zsindex.h"

ZSIndex::ZSIndex(QObject *parent, ZSDatabase *zsdatabase) :
    QObject(parent)
{
    database = zsdatabase;
    latestState = database->getLatestState();
}


void ZSIndex::slotUpdateIndex()
{
    QSqlQuery *query = database->fetchAllChangedEntries();
    if(query == NULL)
    {
        qDebug("ZSIndex:Error: Can't update the index database table!");
        return;
    }
    bool increaseState = false;
    query->last();
    query->first();
    query->previous();
    while(query->next())
    {
        increaseState = true;
        QString newPath = query->value(4).toString();
        int updated = query->value(6).toInt();
        int renamed = query->value(7).toInt();
        int deleted = query->value(8).toInt();

        if(updated == 1)
        {
            database->insertNewIndexEntry(latestState, query->value(0).toString(), "UPD", query->value(1).toLongLong(), query->value(3).toInt(), QString(), query->value(2).toString());
        }
        if(deleted == 1)
        {
            database->insertNewIndexEntry(latestState, query->value(0).toString(), "DEL", query->value(1).toLongLong(), query->value(3).toInt(), QString(), query->value(2).toString());
        }
        if(renamed == 1)
        {
            database->insertNewIndexEntry(latestState, query->value(0).toString(), "REN", query->value(1).toLongLong(), query->value(3).toInt(), newPath, query->value(2).toString());
        }

    }
    if(increaseState)
    {
        increaseLatestState();
    }
    database->resetFileMetaData();
    qDebug() << "INDEX UPDATED!!!";
}

void ZSIndex::increaseLatestState()
{
    latestState++;
}
