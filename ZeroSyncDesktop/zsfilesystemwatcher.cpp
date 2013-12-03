#include "zsfilesystemwatcher.h"


ZSFileSystemWatcher::ZSFileSystemWatcher(QObject *parent, ZSDatabase *zsdatabase) :
    QObject(parent),
    pathToZeroSyncDirectory()
{
    database = zsdatabase;
    fileSystemWatcher = new QFileSystemWatcher();
    establishConnections();
}


void ZSFileSystemWatcher::establishConnections()
{
    connect(fileSystemWatcher, SIGNAL(directoryChanged(QString)), this, SLOT(slotDirectoryChanged(QString)));
    connect(fileSystemWatcher, SIGNAL(fileChanged(QString)), this, SLOT(slotFileChanged(QString)));
}


void ZSFileSystemWatcher::setZeroSyncDirectory(QString pathToDirectory)
{
    pathToZeroSyncDirectory = pathToDirectory;
    setFilesToWatch(pathToZeroSyncDirectory);
}


void ZSFileSystemWatcher::setFilesToWatch(QString path)
{
    fileSystemWatcher->addPath(path);
    QDirIterator directoryIterator(path,  QDir::Files| QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while(directoryIterator.hasNext())
    {
        directoryIterator.next();
        fileSystemWatcher->addPath(directoryIterator.filePath());
        if(directoryIterator.fileInfo().isFile())
        {
            ZSFileMetaData fileMetaData(this, directoryIterator.filePath(), pathToZeroSyncDirectory);
            if(!database->existsFileEntry(fileMetaData.getFilePath()))
            {
                if(database->existsFileHash(fileMetaData.getHash()))
                {
                    if(fileMetaData.getFileSize() > 0)
                    {
                        QString filePathFromHash = database->getFilePathForHash(fileMetaData.getHash());
                        database->setFileChanged(filePathFromHash, 1);
                        database->setFileRenamed(filePathFromHash, 1);
                        database->setFileHashToZero(filePathFromHash);
                        database->setNewPath(filePathFromHash, fileMetaData.getFilePath());
                        addFileToDatabase(directoryIterator.filePath());
                    }
                    else
                    {
                        addFileToDatabase(directoryIterator.filePath());
                    }
                }
                else
                {
                    addFileToDatabase(directoryIterator.filePath());
                }
            }
            else
            {
                if(fileMetaData.getFileSize() < 0)
                {
                    database->setFileChanged(fileMetaData.getFilePath(), 1);
                    database->setFileDeleted(fileMetaData.getFilePath(), 1);
                }
            }
        }
    }
}


void ZSFileSystemWatcher::addFileToDatabase(QString pathToFile)
{
    ZSFileMetaData fileMetaData(this, pathToFile, pathToZeroSyncDirectory);
    database->insertNewFile(fileMetaData.getFilePath(), fileMetaData.getLastModified(), fileMetaData.getHash(), fileMetaData.getFileSize());
}


void ZSFileSystemWatcher::slotDirectoryChanged(QString pathToDirectory)
{
    emit signalDirectoryChangeRecognized(pathToDirectory);
    setFilesToWatch(pathToDirectory);
    qDebug() << "DIRECTORY CHANGED: " << pathToDirectory;
}


void ZSFileSystemWatcher::slotFileChanged(QString pathToFile)
{
    ZSFileMetaData fileMetaData(this, pathToFile, pathToZeroSyncDirectory);
    emit signalFileChangeRecognized(fileMetaData.getFilePath());    
    database->setFileChanged(fileMetaData.getFilePath(), 1);
    database->setFileUpdated(fileMetaData.getFilePath(), 1);
    database->setFileMetaData(fileMetaData.getFilePath(), fileMetaData.getLastModified(), fileMetaData.getHash(), fileMetaData.getFileSize());
    qDebug() << "FILE CHANGED: " << fileMetaData.getFilePath();
}
