#include "zsfilesystemwatcher.h"


ZSFileSystemWatcher::ZSFileSystemWatcher(QObject *parent) :
    QObject(parent)
{
    fileSystemWatcher = new QFileSystemWatcher();
    establishConnections();
}

void ZSFileSystemWatcher::establishConnections()
{
    connect(fileSystemWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(slotDirectoryChanged(QString)));
    connect(fileSystemWatcher, SIGNAL(fileChanged(QString)), this, SLOT(slotFileChanged(QString)));
}


void ZSFileSystemWatcher::addDirectoryToWatch(QString pathToDirectory)
{
    QDir checkDirectoryToWatch(pathToDirectory);
    if(checkDirectoryToWatch.exists())
    {
        fileSystemWatcher->addPath(pathToDirectory);
        this->addFilesToWatch(pathToDirectory);
    }
}


void ZSFileSystemWatcher::removeDirectoryFromWatch(QString pathToDirectory)
{
    QDir checkDirectoryToWatch(pathToDirectory);
    if(checkDirectoryToWatch.exists())
    {
        fileSystemWatcher->removePath(pathToDirectory);
    }
}


void ZSFileSystemWatcher::addFilesToWatch(QString pathToDirectory)
{
    QDirIterator directoryIterator(pathToDirectory, QDirIterator::Subdirectories);
    while(directoryIterator.hasNext())
    {
        fileSystemWatcher->addPath(directoryIterator.filePath());
        directoryIterator.next();
    }
}


void ZSFileSystemWatcher::slotDirectoryChanged(QString pathToDirectory)
{
    qDebug() << pathToDirectory;
}


void ZSFileSystemWatcher::slotFileChanged(QString filePath)
{
    qDebug() << filePath;
}


void ZSFileSystemWatcher::slotDirectoryAboutToBeRemoved(QString pathToDirectory)
{
    removeDirectoryFromWatch(pathToDirectory);
}

