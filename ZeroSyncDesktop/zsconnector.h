#ifndef ZSCONNECTOR_H
#define ZSCONNECTOR_H

#include <QObject>
#include <QtDebug>
#include <QSqlQuery>
#include <zsdatabase.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <zmq.h>
#include <czmq.h>
#include <zyre.h>
#include <zsync.h>


//!  Class that provides the integration of the ZeroSync protocol
/*!
  This class provides the implemention of the ZeroSync protocol, that is used to
  establish connections to other clients and synchronize files between them.
*/
class ZSConnector : public QObject
{

public:
    explicit ZSConnector(QObject *parent = 0);

    void function(void);

private:
    static zlist_t* get_update(uint64_t from_state);
    static void pass_update(char* sender, zlist_t* file_metadata);
    static byte* get_chunk(char* path, uint64_t chunk_size, uint64_t offset);
    static void pass_chunk(byte* chunk, char* path, uint64_t sequence, uint64_t offset);
    static uint64_t get_current_state();

    static zsync_agent_t *agent;

signals:

public slots:

};

#endif // ZSCONNECTOR_H
