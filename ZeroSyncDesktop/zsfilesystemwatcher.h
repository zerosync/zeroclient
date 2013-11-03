#ifndef ZSFILESYSTEMWATCHER_H
#define ZSFILESYSTEMWATCHER_H

#include <QObject>
#include <QFileSystemWatcher>
#include <QDir>
#include <QtDebug>
#include <QDirIterator>

class ZSFileSystemWatcher : public QObject
{
    Q_OBJECT

public:
    explicit ZSFileSystemWatcher(QObject *parent = 0);
    void addDirectoryToWatch(QString);
    void removeDirectoryFromWatch(QString);

private:
    QFileSystemWatcher *fileSystemWatcher;
    void establishConnections();
    void addFilesToWatch(QString);

signals:

private slots:
    void slotDirectoryChanged(QString);
    void slotFileChanged(QString);

public slots:
    void slotDirectoryAboutToBeRemoved(QString);
};

#endif // ZSFILESYSTEMWATCHER_H
