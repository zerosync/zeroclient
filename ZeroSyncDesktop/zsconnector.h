#ifndef ZSCONNECTOR_H
#define ZSCONNECTOR_H

#include <QObject>
#include <QtDebug>
#include <QSqlQuery>
#include <QDir>
#include <QFile>
#include <zsdatabase.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <zmq.h>
#include <czmq.h>
#include <zyre.h>
#include <zsync.h>
#include <zssettings.h>


//!  Class that provides the integration of the ZeroSync protocol
/*!
  This class provides the implemention of the ZeroSync protocol, that is used to
  establish connections to other clients and synchronize files between them.
*/
class ZSConnector : public QObject
{
    Q_OBJECT

public:
    explicit ZSConnector(QObject *parent = 0);

private:
    static zlist_t* get_update(uint64_t from_state);
    static void pass_update(char* sender, zlist_t* file_metadata);
    static zchunk_t* get_chunk(char* path, uint64_t chunk_size, uint64_t offset);
    static void pass_chunk(zchunk_t *chunk, char* path, uint64_t sequence, uint64_t offset);
    static uint64_t get_current_state();
    static zsync_agent_t *agent;

signals:

public slots:
    void slotSynchronizeUpdate(int lastestState);

};

#endif // ZSCONNECTOR_H
