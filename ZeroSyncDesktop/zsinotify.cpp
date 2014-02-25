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

#include "zsinotify.h"

void ZSInotify::run() {

    char *syncdir = ZSSettings::getInstance()->getZeroSyncDirectory().toLatin1().data();


    int EVENT_LEN = sizeof( struct inotify_event );
    int BUF_LEN = 1024 * ( EVENT_LEN + 16 );
    int inotify, wd;
    char buf[BUF_LEN];
    ssize_t numRead;
    char *p;
    struct inotify_event *event;

    // Create inotify instance
    inotify = inotify_init();

    wd = inotify_add_watch( inotify, syncdir, IN_ALL_EVENTS );

    for (;;) {
        numRead = read(inotify, buf, BUF_LEN);

        // Process all of the events in buffer returned by read()
        for (p = buf; p < buf + numRead; ) {
            event = (struct inotify_event *) p; // retrieve the p'th event
            handler(event); // handle it
            p += EVENT_LEN + event->len; // point to next event
        }
    }

}

void ZSInotify::handler( struct inotify_event *event ) {
    char fType[100];
    char action[100];
    bool isDir = false;

    QString path(event->name);

    // Is it a file or a directory?
    if ( event->mask & IN_ISDIR ) {
        isDir = true;
        strcpy( fType, "directory" );
    } else {
        strcpy( fType, "file" );
        isDir = false;
    }

    // What event triggered?
    if (event->mask & IN_ACCESS)
        strcpy(action, "accessed"); // NO ACTION
    else if (event->mask & IN_ATTRIB)
        strcpy(action, "modified ( attributes )"); // NO ACTION
    else if (event->mask & IN_CLOSE_NOWRITE)
        strcpy(action, "closed after being open in read-only"); // NO ACTION
    else if (event->mask & IN_CLOSE_WRITE) {
        strcpy(action, "closed after being open in read-write"); // ACTION: Prepare UPD update
        if(!isDir) {
            fileUpdated(path);
        }
    }
    else if (event->mask & IN_CREATE)
        strcpy(action, "created"); // ACTION: Prepare UPD update / Add watchdir, prepare UPD update
    else if (event->mask & IN_DELETE) {
        strcpy(action, "deleted"); // ACTION: Prepare DEL update / Remove watchdir, prepare DEL update
        if(!isDir) {
            fileDeleted(path);
        }
    }
    else if (event->mask & IN_DELETE_SELF)
        strcpy(action, "deleted and is the watched directory/file"); // ACTION: STOP programm
    else if (event->mask & IN_MODIFY)
        strcpy(action, "modified"); // ACTION: Prepare UPD update
    else if (event->mask & IN_MOVED_FROM)
        strcpy(action, "moved from watched directory"); // ACTION: Prepare DEL update / remove watchdir, prepare DEL update
    else if (event->mask & IN_MOVED_TO)
        strcpy(action, "moved into watched directory"); // ACTION: Prepare UPD/REN update (cookie) / add watchdir, prepare UPD/REN update
    else if (event->mask & IN_MOVE_SELF)
        strcpy(action, "moved and is the watched directory/file"); // ACTION: STOP programm
    else if (event->mask & IN_OPEN)
        strcpy(action, "opened"); // NO ACTION
    else if (event->mask & IN_UNMOUNT)
        strcpy(action, "on a filesystem which has just be unmounted"); // NO ACTION
    else {
        printf("Unknown event %#x", event->mask);
        return;
    }

    // Print out the info
    printf("The %s /%s was %s. (%d)\n", fType, event->name, action, event->cookie);
}

void ZSInotify::fileUpdated(QString path) {
    int length = ZSSettings::getInstance()->getZeroSyncDirectory().length();
    QFileInfo file(path);
    qint64 timestamp = file.lastModified().toUTC().toMSecsSinceEpoch();
    QString hash = calculateHash(path);
    qint64 filesize = file.size();
    path.remove(0, length);

    ZSDatabase::getInstance()->setFileChanged(path, 1);
    ZSDatabase::getInstance()->setFileUpdated(path, 1);
    ZSDatabase::getInstance()->setFileDeleted(path, 0);
    ZSDatabase::getInstance()->setFileMetaData(path, timestamp, hash, filesize);
}

void ZSInotify::fileMovedIn(QString path, quint32 ref) {
    int length = ZSSettings::getInstance()->getZeroSyncDirectory().length();
    QFileInfo file(path);
    qint64 timestamp = file.lastModified().toUTC().toMSecsSinceEpoch();
    QString hash = calculateHash(path);
    qint64 filesize = file.size();
    path.remove(0, length);

    ZSDatabase::getInstance()->setFileChanged(path, 1);
    ZSDatabase::getInstance()->setFileUpdated(path, 1);
    ZSDatabase::getInstance()->setFileDeleted(path, 0);
    ZSDatabase::getInstance()->setFileMetaData(path, timestamp, hash, filesize);

    if (ref > 0) {
        // TODO: change DEL to REN
    }
}

void ZSInotify::fileMovedOut(QString path, quint32 ref) {
    int length = ZSSettings::getInstance()->getZeroSyncDirectory().length();
    path.remove(0, length);

    ZSDatabase::getInstance()->setFileChanged(path, 1);
    ZSDatabase::getInstance()->setFileUpdated(path, 0);
    ZSDatabase::getInstance()->setFileDeleted(path, 1);
    ZSDatabase::getInstance()->setFileReference(path, ref);
    ZSDatabase::getInstance()->setFileTimestamp(path, QDateTime::currentDateTime().toUTC().toMSecsSinceEpoch());
}

void ZSInotify::fileDeleted(QString path) {
    int length = ZSSettings::getInstance()->getZeroSyncDirectory().length();
    path.remove(0, length);

    ZSDatabase::getInstance()->setFileChanged(path, 1);
    ZSDatabase::getInstance()->setFileUpdated(path, 0);
    ZSDatabase::getInstance()->setFileDeleted(path, 1);
    ZSDatabase::getInstance()->setFileTimestamp(path, QDateTime::currentDateTime().toUTC().toMSecsSinceEpoch());
}


QString ZSInotify::calculateHash(QString path)
{
    QCryptographicHash cryptoHash(QCryptographicHash::Sha3_512);
    QFile file(path);
    file.open(QFile::ReadOnly);
    cryptoHash.addData(file.readAll());
    QByteArray hashValue = cryptoHash.result();
    return hashValue.toHex();
}
