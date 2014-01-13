#include "zsconnector.h"

extern "C"
{
    #include <czmq.h>
    #include <zyre.h>
    #include <zyre_event.h>
    #include <zs_fmetadata.h>
    #include <zs_msg.h>
    #include <zsync_peer.h>
    #include <zsync_ftmanager.h>
    #include <zsync_node.h>
    #include <zsync_agent.h>
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
}

void ZSConnector::get_update()
{

}

void ZSConnector::pass_update()
{

}

void ZSConnector::get_chunk()
{

}

void ZSConnector::pass_chunk()
{

}

void ZSConnector::get_current_state()
{

}
}
