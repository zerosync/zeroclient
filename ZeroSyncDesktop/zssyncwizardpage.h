/* =========================================================================
   ZSSyncWizardPage - This wizardpage is part of the setup wizard
   to configure the ZeroSync desktop client

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
    //!  Constructor
    /*!
      The default constructor.
    */
    explicit ZSSyncWizardPage();

private:
    //!  SyncIntervalLabel
    /*!
      Label that holds the sync interval text.
    */
    QLabel *syncIntervalLabel;

    //!  SyncIntervalMinLabel
    /*!
      Label that holds the minimum sync interval text.
    */
    QLabel *labelSyncIntervalMin;

    //!  SyncIntervalMaxLabel
    /*!
      Label that holds the maximum sync interval text.
    */
    QLabel *labelSyncIntervalMax;

    //!  SyncIntervalValueLabel
    /*!
      Label that holds the sync interval value.
    */
    QLabel *labelSyncIntervalValue;

    //!  GridLayout
    /*!
      The layout for the gui elements.
    */
    QGridLayout *layout;

    //!  SyncIntervalSlider
    /*!
      Slider that is used to set the sync interval.
    */
    QSlider *sliderSyncInterval;

signals:

public slots:

private slots:
    //!  IntervalChange-Slot
    /*!
      This slot is used when the user changes the synchronization interval in the option window.
    */
    void slotSliderSyncIntervalChanged(int);

};

#endif // ZSSYNCWIZARDPAGE_H
