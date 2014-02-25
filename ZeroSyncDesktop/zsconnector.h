/* =========================================================================
   ZSConnector - Interface between the desktop client and the protocol


   -------------------------------------------------------------------------
   Copyright (c) 2014 Kevin Sapper, Tommy Bluhm
   Copyright other contributors as noted in the AUTHORS file.

   This file is part of ZeroSync, see http://zerosync.org.

   This is free software; you can redistribute it and/or modify it under
   the terms of the GNU Lesser General Public License as published by the
   Free Software Foundation; either version 3 of the License, or (at your
   option) any later version.
   This software is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTA-
   BILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General
   Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program. If not, see http://www.gnu.org/licenses/.
   =========================================================================
*/

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
    void slotSynchronizeUpdate();

};

#endif // ZSCONNECTOR_H
