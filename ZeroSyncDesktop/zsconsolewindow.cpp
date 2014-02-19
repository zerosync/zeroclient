#include "zsconsolewindow.h"

ZSConsoleWindow::ZSConsoleWindow(QObject *parent, bool newDirectory) :
    QObject(parent)
{
    if(newDirectory)
    {
        ZSDatabase::getInstance()->deleteAllRowsFromFilesTable();
        ZSDatabase::getInstance()->setZeroSyncFolderChangedFlagToFileIndexTable();
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

