#ifndef ZSCONNECTOR_H
#define ZSCONNECTOR_H

#include <QObject>
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <QtDebug>

class ZSConnector : public QObject
{

public:
    explicit ZSConnector(QObject *parent = 0);

private:
//    static zlist_t* get_update(u_int64_t from_state);
//    static void pass_update(char* sender, zlist_t* file_metadata);
//    static byte* get_chunk(char* path, u_int64_t chunk_size, u_int64_t offset);
//    static void pass_chunk(byte* chunk, char* path, u_int64_t sequence, u_int64_t offset);
//    static u_int64_t get_current_state();

signals:

public slots:

};

#endif // ZSCONNECTOR_H
