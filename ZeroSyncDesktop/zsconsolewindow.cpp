#include "zsconsolewindow.h"

ZSConsoleWindow::ZSConsoleWindow(QObject *parent, QString path, int interval) :
    QObject(parent)
{
    if(!ZSSettings::getInstance()->existSettings())
    {
        ZSSettings::getInstance()->setZeroSyncDirectory(path);
        ZSSettings::getInstance()->setSyncInterval(interval);
    }

    fileSystemWatcher = new ZSFileSystemWatcher();
    fileSystemWatcher->setZeroSyncDirectory(ZSSettings::getInstance()->getZeroSyncDirectory());
    index = new ZSIndex();
    connector = new ZSConnector();
    htmlBuilder = new ZShtmlBuilder();

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), index, SLOT(slotUpdateIndex()));

    if(ZSSettings::getInstance()->getSyncInterval() > 0)
    {
        index->slotUpdateIndex();
        timer->start(ZSSettings::getInstance()->getSyncInterval());
    }

    QDir directoryOfIndexFile("");
    directoryOfIndexFile.mkpath(QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0));
}

