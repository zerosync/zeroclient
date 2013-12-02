#ifndef ZSFILESYSTEMWATCHER_H
#define ZSFILESYSTEMWATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QDir>
#include <QtDebug>
#include <QDirIterator>
#include <QCryptographicHash>
#include <QDateTime>
#include <QStandardPaths>
#include "zsdatabase.h"
#include "zsfilemetadata.h"
#include "zsindex.h"

class ZSFileSystemWatcher : public QObject
{
    Q_OBJECT

public:
    explicit ZSFileSystemWatcher(QObject *parent = 0, ZSDatabase *zsdatabase = 0);
    void setZeroSyncDirectory(QString);

private:
    QFileSystemWatcher *fileSystemWatcher;
    QString pathToZeroSyncDirectory;
    ZSDatabase *database;
    void establishConnections();
    void setFilesToWatch(QString);
    void addFileToDatabase(QString);

signals:
    void signalDirectoryChangeRecognized(QString);
    void signalFileChangeRecognized(QString);

private slots:
    void slotDirectoryChanged(QString);
    void slotFileChanged(QString);

};

#endif // ZSFILESYSTEMWATCHER_H
