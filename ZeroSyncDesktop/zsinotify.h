/* =========================================================================
   ZSNotify - Class that implements inotify-specific functionalities


   -------------------------------------------------------------------------
   Copyright (c) 2014 Kevin Sapper
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

#ifndef ZSINOTIFY_H
#define ZSINOTIFY_H

#include <QThread>
#include <QFileInfo>
#include <QDateTime>
#include <QCryptographicHash>
#include <unistd.h>
#include <sys/inotify.h>
#include "zssettings.h"
#include "zsdatabase.h"

class ZSInotify : public QThread
{
    Q_OBJECT

public:
    void run() Q_DECL_OVERRIDE;
    void handler(struct inotify_event *event);

signals:
    void resultReady(const QString &s);

private:
    QString calculateHash(QString path);
    void fileUpdated(QString path);
    void fileMovedIn(QString path, quint32 ref);
    void fileMovedOut(QString path, quint32 ref);
    void fileDeleted(QString path);

public slots:

};

#endif // ZSINOTIFY_H
