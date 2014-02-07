#ifndef ZSCONNECTOR_H
#define ZSCONNECTOR_H

#include <QObject>
#include <QtDebug>
#include <zsdatabase.h>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <zmq.h>
#include <czmq.h>
#include <zyre.h>
#include<zsync.h>

class ZSConnector : public QObject
{

public:
    explicit ZSConnector(QObject *parent = 0, ZSDatabase *zsdatabase = 0);

    void function(void);

private:
    static zlist_t* get_update(uint64_t from_state);
    static void pass_update(char* sender, zlist_t* file_metadata);
    static byte* get_chunk(char* path, uint64_t chunk_size, uint64_t offset);
    static void pass_chunk(byte* chunk, char* path, uint64_t sequence, uint64_t offset);
    static uint64_t get_current_state();

    ZSDatabase *database;

signals:

public slots:

};

#endif // ZSCONNECTOR_H
