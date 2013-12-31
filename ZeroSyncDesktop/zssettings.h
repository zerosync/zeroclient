#ifndef ZSSETTINGS_H
#define ZSSETTINGS_H

#include <QObject>
#include <QSettings>

class ZSSettings : public QObject
{
    Q_OBJECT

public:
    explicit ZSSettings(QObject *parent = 0);
    bool existSettings();
    void setZeroSyncDirectory(QString);
    void setSyncInterval(int);
    QString getZeroSyncDirectory();
    int getSyncInterval();

private:
    QSettings *settings;

signals:

public slots:

};

#endif // ZSSETTINGS_H
