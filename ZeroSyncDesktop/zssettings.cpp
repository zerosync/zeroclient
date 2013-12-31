#include "zssettings.h"

ZSSettings::ZSSettings(QObject *parent) :
    QObject(parent)
{
    settings = new QSettings();
}

bool ZSSettings::existSettings()
{
    if(settings->contains("directory") && settings->contains("syncinterval"))
    {
        return true;
    }
    return false;
}


void ZSSettings::setZeroSyncDirectory(QString path)
{
    settings->setValue("directory", path);
}


void ZSSettings::setSyncInterval(int seconds)
{
    settings->setValue("syncinterval", seconds);
}


QString ZSSettings::getZeroSyncDirectory()
{
    return settings->value("directory").toString();
}


int ZSSettings::getSyncInterval()
{
    return settings->value("syncinterval").toInt();
}
