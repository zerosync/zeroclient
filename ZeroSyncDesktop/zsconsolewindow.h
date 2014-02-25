/* =========================================================================
   ZSConsoleWindow - Class that is used to start ZeroSync as console app


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

#ifndef ZSCONSOLEWINDOW_H
#define ZSCONSOLEWINDOW_H

#include <QObject>
#include <QTimer>
#include "zsfilesystemwatcher.h"
#include "zsdatabase.h"
#include "zsindex.h"
#include "zssetupwizard.h"
#include "zssettings.h"
#include "zsconnector.h"
#include "zshtmlbuilder.h"
#include "zsinotify.h"


class ZSConsoleWindow : public QObject
{
    Q_OBJECT
public:
    //!  Constructor
    /*!
      The default constructor.
    */
    explicit ZSConsoleWindow(QObject *parent = 0, bool newDirectory = false);

private:    
    //!  The ZeroSync FileSystemWatcher
    /*!
      The FileSystemWatcher is used to watch the local filesystem for changes that will be written to the local ZeroSync database.
    */
    ZSFileSystemWatcher *fileSystemWatcher;

    //!  The ZeroSync Index
    /*!
      The index is used to write local filesystem changes to the persistent index that is shared between clients.
    */
    ZSIndex *index;

    //!  The ZeroSync SetupWizard
    /*!
      The setup wizard is used to set up the ZeroSync options.
    */
    ZSSetupWizard *setupWizard;

    //!  The ZeroSync Connector
    /*!
      The connector is used to establish connections between clients with the ZeroSync protocol.
    */
    ZSConnector *connector;

    //!  The ZeroSync HTMLBuilder
    /*!
      The html builder is used to build the ZeroSyncWebIndex html file.
    */
    ZShtmlBuilder *htmlBuilder;

    //!  ZSNotify
    /*!
      This class is used to implement some inotify specific functionalities.
    */
    ZSInotify *inotify;

    //!  Method to establish UI-Connections
    /*!
      This method is used to establish most of the signal-slot-connections within the mainwindow class.
    */

    //!  Synchronization-Timer
    /*!
      This timer is used to synchronize ZeroSync periodically.
    */
    QTimer *timer;

signals:

public slots:

};

#endif // ZSCONSOLEWINDOW_H
