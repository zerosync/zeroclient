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


#ifndef ZSSETTINGS_H
#define ZSSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QMutex>


//!  Class that provides the local ZeroSync settings
/*!
  This class is used to read or write local ZeroSync settings like
  the path to the ZeroSync folder or the sychronization interval.
*/
class ZSSettings : public QObject
{
    Q_OBJECT

public:
    //!  GetInstance-Function
    /*!
      Static function that implements the Singleton functionality.
    */
    static ZSSettings* getInstance()
    {
        static QMutex mutex;
        if (!m_Instance)
        {
            mutex.lock();
            if (!m_Instance)
            {
                m_Instance = new ZSSettings();
            }
            mutex.unlock();
        }
        return m_Instance;
    }

    //!  DeleteInstance-Function
    /*!
      Static function that is used to delete the actual Singleton instance.
    */
    static void deleteInstance()
    {
        static QMutex mutex;
        mutex.lock();
        delete m_Instance;
        m_Instance = 0;
        mutex.unlock();
    }

    //!  ExistSettings-Method
    /*!
      Is used to check if the settings are already saved persistently.
    */
    bool existSettings();

    //!  SetZeroSyncDirectory-Method
    /*!
      Is used to save the path to the ZeroSync directory persistently.
    */
    void setZeroSyncDirectory(QString);

    //!  SetSyncInterval-Method
    /*!
      Is used to save the sync interval persistently.
    */
    void setSyncInterval(int);

    //!  GetZeroSyncDirectory-Method
    /*!
      Is used to load the persistently saved path to the ZeroSync Directory.
    */
    QString getZeroSyncDirectory();

    //!  GetSyncInterval-Method
    /*!
      Is used to load the persistently saved sync interval.
    */
    int getSyncInterval();

private:
    //!  "Disabled" Constructor
    /*!
      Constructor that is set to private to implement the Singleton functionality.
    */
    ZSSettings();

    //!  "Disabled" Constructor
    /*!
      Constructor that is set to private to implement the Singleton functionality.
    */
    ZSSettings(const ZSSettings &);

    //!  "Disabled" Operator
    /*!
      Operator that is set to private to implement the Singleton functionality.
    */
    ZSSettings& operator=(const ZSSettings &);

    //!  ZSettings Singleton Instance
    /*!
      Instance that can be requested with the getInstance-Method.
    */
    static ZSSettings* m_Instance;

    //!  QSettings-Class
    /*!
      To save the options persistently the functionality of the QSettings class is used.
    */
    QSettings settings;

signals:

public slots:

};

#endif // ZSSETTINGS_H
