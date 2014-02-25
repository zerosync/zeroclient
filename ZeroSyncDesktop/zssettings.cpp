/* =========================================================================
   ZSSettings - User settings class for the ZeroSync desktop client


   -------------------------------------------------------------------------
   Copyright (c) 2014 Tommy Bluhm
   Copyright other contributors as noted in the AUTHORS file.

   This file is part of ZeroSync, see http://zerosync.org.

   This is free software; you can redistribute it and/or modify it under
   the terms of the GNU Lesser General Public License as published by the
   Free Software Foundation; either version 3 of the License, or (at your
   option) any later version.
   This software is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTA-
   BILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General
   Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program. If not, see http://www.gnu.org/licenses/.
   =========================================================================
*/


#include "zssettings.h"

ZSSettings* ZSSettings::m_Instance = 0;

ZSSettings::ZSSettings() :
    settings()
{

}

bool ZSSettings::existSettings()
{
    if(settings.contains("directory") && settings.contains("syncinterval"))
    {
        return true;
    }
    return false;
}


void ZSSettings::setZeroSyncDirectory(QString path)
{
    settings.setValue("directory", path);
}


void ZSSettings::setSyncInterval(int seconds)
{
    settings.setValue("syncinterval", seconds);
}


QString ZSSettings::getZeroSyncDirectory()
{
    return settings.value("directory").toString();
}


int ZSSettings::getSyncInterval()
{
    return settings.value("syncinterval").toInt();
}
