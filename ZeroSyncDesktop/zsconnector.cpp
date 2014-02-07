#include "zsconnector.h"

ZSConnector::ZSConnector(QObject *parent, ZSDatabase *zsdatabase) :
    QObject(parent)
{
    database = zsdatabase;

    zsync_agent_t *zsAgent;
    zsAgent = zsync_agent_new();
    zsync_agent_set_get_update(zsAgent, (void *) &ZSConnector::get_update);
    zsync_agent_set_pass_update(zsAgent, (void *) &ZSConnector::pass_update);

    zsync_agent_set_get_chunk(zsAgent, (void *) &ZSConnector::get_chunk);
    zsync_agent_set_pass_chunk(zsAgent, (void *) &ZSConnector::pass_chunk);

    zsync_agent_set_get_current_state(zsAgent, (void *) &ZSConnector::get_current_state);

    qDebug() << zsync_agent_start(zsAgent);
}

zlist_t* ZSConnector::get_update(uint64_t from_state)
{
    qDebug() << "get_update";
    return NULL;
}

void ZSConnector::pass_update(char* sender, zlist_t* file_metadata)
{
    qDebug() << "pass_update";
}

byte* ZSConnector::get_chunk(char* path, uint64_t chunk_size, uint64_t offset)
{
    qDebug() << "get_chunk";
    return NULL;
}

void ZSConnector::pass_chunk(byte *chunk, char *path, uint64_t sequence, uint64_t offset)
{
    qDebug() << "pass_chunk";
}

uint64_t ZSConnector::get_current_state()
{
    qDebug() << "current_state";
    return database->getLatestState();
}


