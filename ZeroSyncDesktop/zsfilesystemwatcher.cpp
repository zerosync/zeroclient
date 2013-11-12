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
    resetWatchList();
    deleteIndexFile();
    updateFilesToWatch();
}


void ZSFileSystemWatcher::updateFilesToWatch()
{
    fileSystemWatcher->addPath(pathToZeroSyncDirectory);
    QDirIterator directoryIterator(pathToZeroSyncDirectory,  QDir::Files| QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    while(directoryIterator.hasNext())
    {
        directoryIterator.next();
        fileSystemWatcher->addPath(directoryIterator.filePath());
        if(directoryIterator.fileInfo().isFile())
        {
            saveFileToIndex(directoryIterator.filePath());
        }
    }
}

void ZSFileSystemWatcher::saveFileToIndex(QString pathToFile)
{
    QFile watchListFile(getIndexFilePath());
    if(watchListFile.open(QFile::WriteOnly | QFile::Append))
    {
        QFileInfo fileInformations(pathToFile);
        QString filePath = fileInformations.absoluteFilePath().remove(0, pathToZeroSyncDirectory.length() + 1);
        qint64 fileLastModified = fileInformations.lastModified().toUTC().toMSecsSinceEpoch();
        QString hashOfFile = QCryptographicHash::hash(pathToFile.toStdString().c_str(), QCryptographicHash::Sha3_512).toHex();
        QTextStream stream(&watchListFile);
        stream << filePath << ";" << fileLastModified << ";" << hashOfFile << "\n";
        watchListFile.close();
    }
}

void ZSFileSystemWatcher::slotDirectoryChanged(QString pathToDirectory)
{
    emit signalDirectoryChangeRecognized(pathToDirectory);
    qDebug() << "DIRECTORY CHANGED: " << pathToDirectory;
    resetWatchList();
    deleteIndexFile();
    updateFilesToWatch();
}


void ZSFileSystemWatcher::slotFileChanged(QString pathToFile)
{
    emit signalFileChangeRecognized(pathToFile);
    qDebug() << "FILE CHANGED: " << pathToFile;
    resetWatchList();
    deleteIndexFile();
    updateFilesToWatch();
}

void ZSFileSystemWatcher::deleteIndexFile()
{
    QFile watchListFile(getIndexFilePath());
    watchListFile.remove();
}

void ZSFileSystemWatcher::resetWatchList()
{
    fileSystemWatcher->removePaths(fileSystemWatcher->files());
}

QString ZSFileSystemWatcher::getIndexFilePath()
{
    qDebug() << QString(QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0) + "/index.csv");
    return QString(QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0) + "/index.csv");
}
