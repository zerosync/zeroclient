#include "zsfilesystemwatcher.h"


ZSFileSystemWatcher::ZSFileSystemWatcher(QObject *parent) :
    QObject(parent),
    pathToZeroSyncDirectory()
{
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
    updateFilesToWatch();
}


void ZSFileSystemWatcher::updateFilesToWatch()
{
    QDirIterator directoryIterator(pathToZeroSyncDirectory, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while(directoryIterator.hasNext())
    {
        fileSystemWatcher->addPath(directoryIterator.filePath());
        saveFileToWatchListCSV(directoryIterator.filePath());
        qDebug() << directoryIterator.filePath();
        directoryIterator.next();
    }
}

void ZSFileSystemWatcher::saveFileToWatchListCSV(QString pathToFile)
{
    QFile watchListFile("watchlist.csv");
    if(watchListFile.open(QFile::WriteOnly|QFile::Append))
    {
        QFileInfo fileInformations(pathToFile);
        QString fileName = fileInformations.fileName();
        QString fileLastModified = fileInformations.lastModified().toUTC().toString();
        QString hashOfFile = QCryptographicHash::hash(pathToFile.toStdString().c_str(), QCryptographicHash::Sha3_512).toHex();
        QTextStream stream(&watchListFile);
        stream << fileName << ";" << pathToFile << ";" << fileLastModified << ";" << hashOfFile << "\n";
        watchListFile.close();
    }
}

void ZSFileSystemWatcher::slotDirectoryChanged(QString pathToDirectory)
{
    emit signalDirectoryChangeRecognized(pathToDirectory);
    updateFilesToWatch();

    qDebug() << pathToDirectory;
}


void ZSFileSystemWatcher::slotFileChanged(QString pathToFile)
{
    emit signalFileChangeRecognized(pathToFile);
    updateFilesToWatch();

    qDebug() << pathToFile;
}

