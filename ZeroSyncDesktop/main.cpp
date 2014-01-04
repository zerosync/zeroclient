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
