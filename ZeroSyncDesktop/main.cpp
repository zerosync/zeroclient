#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    a.setApplicationName("ZeroSync");
    a.setOrganizationName("ZeroSync Team");
    a.setOrganizationDomain("zerosync.org");

    MainWindow w;

    // This is commented out because we want to have Zerosync started to tray
    //w.show();

    return a.exec();
}
