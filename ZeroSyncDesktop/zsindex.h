/* =========================================================================
   ZSIndex - Filesystem indexing class for the ZeroSync desktop client


   -------------------------------------------------------------------------
   Copyright (c) 2014 Tommy Bluhm
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


//!  Class that provides the ZeroSync index functionality
/*!
  This class is used to update the ZeroSync index within the local
  SQLite database.
*/
class ZSIndex : public QObject
{
    Q_OBJECT

public:
    //!  Constructor
    /*!
      The default constructor.
    */
    explicit ZSIndex(QObject *parent = 0);

    //!  Deconstructor
    /*!
      The default deconstructor.
    */
    void increaseLatestState();

private:
    //!  LastState-Variable
    /*!
      Variable that holds the value of the last state that was saved to the local index.
    */
    int latestState;

signals:
    //!  IndexUpdated-Signal
    /*!
      Signal that is emitted right after the index was updated.
    */
    void signalIndexUpdated();

public slots:
    //!  UpdateIndex-Slot
    /*!
      Slot that is used to update the index with new values.
    */
    void slotUpdateIndex();

};

#endif // ZSINDEX_H
