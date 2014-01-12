#ifndef ZSCONNECTOR_H
#define ZSCONNECTOR_H

#include <QObject>
#include <cinttypes>
#include <cstdlib>
#include <cstdio>

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

class ZSConnector : public QObject
{
    Q_OBJECT
public:
    explicit ZSConnector(QObject *parent = 0);

private:
    zsync_agent_t *zsAgent;
    static void pass_update();
    static void get_update();
    static void pass_chunk();
    static void get_chunk();
    static void get_current_state();

signals:

public slots:

};

#endif // ZSCONNECTOR_H
