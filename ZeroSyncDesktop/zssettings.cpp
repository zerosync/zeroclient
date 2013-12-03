#include "zssettings.h"

ZSSettings::ZSSettings(QObject *parent) :
    QObject(parent),
    settings()
{

}

bool ZSSettings::existSettings()
{
    if(settings.contains("chunksize") && settings.contains("directory") && settings.contains("synctimer") && settings.contains("database"))
    {
        return true;
    }
    return false;
}

void ZSSettings::setChunkSize(int chunkSize)
{
    settings.setValue("chunksize", chunkSize);
}


void ZSSettings::setZeroSyncDirectory(QString path)
{
    settings.setValue("directory", path);
}


void ZSSettings::setTimeBetweenSyncs(int seconds)
{
    settings.setValue("synctimer", seconds);
}

void ZSSettings::setDatabaseDirectory(QString path)
{
    settings.setValue("database", path);
}


int ZSSettings::getChunkSize()
{
    return settings.value("chunksize").toInt();
}


QString ZSSettings::getZeroSyncDirectory()
{
    return settings.value("directory").toString();
}


int ZSSettings::getTimeBetweenSyncs()
{
    return settings.value("synctimer").toInt();
}

QString ZSSettings::getDatabaseDirectory()
{
    return settings.value("database").toString();
}
