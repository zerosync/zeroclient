#ifndef ZSSETTINGS_H
#define ZSSETTINGS_H

#include <QObject>
#include <QSettings>

class ZSSettings : public QObject
{
    Q_OBJECT

public:
    explicit ZSSettings(QObject *parent = 0);
    void setChunkSize(int);
    void setZeroSyncDirectory(QString);
    void setTimeBetweenSyncs(int);
    void setDatabaseDirectory(QString);
    int getChunkSize();
    QString getZeroSyncDirectory();
    int getTimeBetweenSyncs();
    QString getDatabaseDirectory();
    bool existSettings();

private:
    QSettings settings;

signals:

public slots:

};

#endif // ZSSETTINGS_H
