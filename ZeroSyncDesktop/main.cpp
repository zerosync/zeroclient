/* =========================================================================
   Main - Process entry point for the ZeroSync desktop client


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


#include "mainwindow.h"
#include <QApplication>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    a.setApplicationName("ZeroSync");
    a.setOrganizationName("ZeroSyncTeam");
    a.setOrganizationDomain("zerosync.org");


//    a.processEvents();

//    // GUID generated for ZeroSync
//    QSharedMemory zsGuid("bf2a7f32-3e2c-4b93-aefd-ce948be880a8");

//    // This ensures that only one instance of Zerosync can be active
//    if(!zsGuid.create(512, QSharedMemory::ReadWrite))
//    {
//        QMessageBox::information(0, "ZeroSync", "ZeroSync is already running!", QMessageBox::Ok, QMessageBox::Ok);
//        qDebug() << "User tried to start another instance of ZeroSync - aborted";
//        exit(0);
//    }
//    else
//    {
//        qDebug() << "ZeroSync started sucessfully";
//    }

    MainWindow w;

    // This is commented out because we want to have Zerosync started to tray
    //w.show();

    return a.exec();
}
