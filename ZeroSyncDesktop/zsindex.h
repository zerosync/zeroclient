/* =========================================================================
   ZSIndex - Filesystem indexing class for the ZeroSync desktop client


   -------------------------------------------------------------------------
   Copyright (c) 2013 Tommy Bluhm
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


#ifndef ZSINDEX_H
#define ZSINDEX_H

#include <QObject>
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include "zsdatabase.h"
#include "zsfilemetadata.h"

class ZSIndex : public QObject
{
    Q_OBJECT

public:
    explicit ZSIndex(QObject *parent = 0, ZSDatabase *zsdatabase = 0);
    void increaseLatestState();

private:
    ZSDatabase *database;
    int latestState;

signals:

public slots:
    void slotUpdateIndex();

};

#endif // ZSINDEX_H
