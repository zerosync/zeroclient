#ifndef ZSINOTIFY_H
#define ZSINOTIFY_H

#include <QThread>
#include <QFileInfo>
#include <QDateTime>
#include <QCryptographicHash>
#include <unistd.h>
#include <sys/inotify.h>
#include "zssettings.h"
#include "zsdatabase.h"

class ZSInotify : public QThread
{
    Q_OBJECT

public:
    void run() Q_DECL_OVERRIDE;
    void handler(struct inotify_event *event);

signals:
    void resultReady(const QString &s);

private:
    QString calculateHash(QString path);
    void fileUpdated(QString path);
    void fileMovedIn(QString path, quint32 ref);
    void fileMovedOut(QString path, quint32 ref);
    void fileDeleted(QString path);

public slots:

};

#endif // ZSINOTIFY_H
