#include "zsconnector.h"

ZSConnector::ZSConnector(QObject *parent) :
    QObject(parent)
{
    typedef unsigned char byte;

    zsAgent = zsync_agent_new();

    zsync_agent_set_get_update(zsAgent, (void*) (get_update));
    zsync_agent_set_pass_update(zsAgent, (void*) (pass_update));

    zsync_agent_set_get_chunk(zsAgent, (void*) (get_chunk));
    zsync_agent_set_pass_chunk(zsAgent, (void*) (pass_chunk));

    zsync_agent_set_get_current_state(zsAgent, (void*) (get_current_state));
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
