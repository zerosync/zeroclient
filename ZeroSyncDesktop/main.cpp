#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("ZeroSync");
    a.setOrganizationName("ZeroSync Team");
    MainWindow w;
    w.show();

    return a.exec();
}