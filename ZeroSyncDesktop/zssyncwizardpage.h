/* =========================================================================
   ZSSyncWizardPage - This wizardpage is part of the setup wizard
   to configure the ZeroSync desktop client

   -------------------------------------------------------------------------
   Copyright (c) 2013 Tommy Bluhm
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


#ifndef ZSSYNCWIZARDPAGE_H
#define ZSSYNCWIZARDPAGE_H

#include <QObject>
#include <QWizardPage>
#include <QLabel>
#include <QGridLayout>
#include <QtDebug>
#include <QSlider>


//!  Class that provides an wizardpage to configure ZeroSync synchronization options
/*!
  Is used by the class ZSSetupWizard and provides a setup page to configure synchronization
  intervals.
*/
class ZSSyncWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit ZSSyncWizardPage();

private:
    QLabel *syncIntervalLabel;
    QLabel *labelSyncIntervalMin;
    QLabel *labelSyncIntervalMax;
    QLabel *labelSyncIntervalValue;
    QGridLayout *layout;
    QSlider *sliderSyncInterval;

signals:

public slots:

private slots:
    void slotSliderSyncIntervalChanged(int);

};

#endif // ZSSYNCWIZARDPAGE_H
