/* =========================================================================
   Main - Process entry point for the ZeroSync desktop client


   -------------------------------------------------------------------------
   Copyright (c) 2014 Tommy Bluhm, Kevin Sapper
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
#include "zsconsolewindow.h"
#include <QCoreApplication>
#include <QApplication>
#include <QDir>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        QCoreApplication a(argc, argv);
        a.setApplicationName("ZeroSync");
        a.setOrganizationName("ZeroSyncTeam");
        a.setOrganizationDomain("zerosync.org");
        a.setApplicationVersion("1.0");

        bool newDirectory = false;

        QCommandLineParser parser;
        parser.setApplicationDescription("ZeroSync Help:");
        parser.addHelpOption();
        parser.addVersionOption();

        QCommandLineOption consoleOption(QStringList() << "c" << "console", "Start as console application without GUI.");
        parser.addOption(consoleOption);

        parser.process(a);

        if(parser.isSet(consoleOption))
        {
            if(!ZSSettings::getInstance()->existSettings())
            {
                newDirectory = true;
                QTextStream(stdout) << "Please insert absolute path to sync directory:\n>> ";
                QTextStream qtin(stdin);
                QString path = qtin.readLine();
                QDir syncDir(path);
                if(syncDir.exists()) {
                    ZSSettings::getInstance()->setZeroSyncDirectory(path);
                } else {
                    QTextStream(stdout) << "Invalid path!\n";
                    exit(0);
                }
                QTextStream(stdout) << "Please insert an interval in seconds to check for changes:\n>> ";
                bool isInt = false;
                int interval = qtin.readLine().toInt(&isInt, 10) * 1000;
                if (isInt) {
                    qDebug() << interval;
                    ZSSettings::getInstance()->setSyncInterval(interval);
                } else {
                    QTextStream(stdout) << "Invalid interval!\n";
                    exit(0);
                }
            }
        }


        ZSConsoleWindow z(NULL, newDirectory);

        return a.exec();
    }
    else
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

}
