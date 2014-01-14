#include "zsconnector.h"
extern "C"
{
    #include "czmq.h"
    #include "zyre.h"
    #include "zyre_event.h"
    #include "zs_fmetadata.h"
    #include "zs_msg.h"
    #include "zsync_peer.h"
    #include "zsync_ftmanager.h"
    #include "zsync_node.h"
    #include "zsync_agent.h"
}

zlist_t* get_update(uint64_t from_state)
{

}

void pass_update(char* sender, zlist_t* file_metadata)
{

}

byte* get_chunk(char* path, uint64_t chunk_size, uint64_t offset)
{

}

void pass_chunk(byte *chunk, char *path, uint64_t sequence, uint64_t offset)
{

}

u_int64_t get_current_state()
{
    return 0;
}

ZSConnector::ZSConnector(QObject *parent) :
    QObject(parent)
{
    zsync_agent_t *zsAgent;
    zsAgent = zsync_agent_new();
    zsync_agent_set_get_update(zsAgent, (void*) get_update);
    zsync_agent_set_pass_update(zsAgent, (void*) pass_update);

    zsync_agent_set_get_chunk(zsAgent, (void*) get_chunk);
    zsync_agent_set_pass_chunk(zsAgent, (void*) pass_chunk);

    zsync_agent_set_get_current_state(zsAgent, (void*) get_current_state);

    qDebug() << zsync_agent_start(zsAgent);
}


