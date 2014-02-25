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


#include "zssyncwizardpage.h"

ZSSyncWizardPage::ZSSyncWizardPage() :
    QWizardPage()
{
    setTitle("Setting the synchronization options");
    setSubTitle("Here can you set your preferred time between synchronizations");

    sliderSyncInterval = new QSlider(Qt::Horizontal);
    sliderSyncInterval->setMinimum(0);
    sliderSyncInterval->setMaximum(3600000);
    sliderSyncInterval->setTickInterval(60000);
    sliderSyncInterval->setTickPosition(QSlider::TicksBothSides);
    sliderSyncInterval->setSingleStep(10000);
    sliderSyncInterval->setPageStep(60000);

    syncIntervalLabel = new QLabel("Choose synchronization interval:");
    labelSyncIntervalMin = new QLabel("Manual");
    labelSyncIntervalMax = new QLabel("60 Minutes");
    labelSyncIntervalValue = new QLabel("<b>Manual</b>");
    labelSyncIntervalValue->setAlignment(Qt::AlignCenter);

    layout = new QGridLayout;
    layout->addWidget(syncIntervalLabel, 0, 1);
    layout->addWidget(labelSyncIntervalValue, 1, 1);
    layout->addWidget(labelSyncIntervalMin, 2, 0);
    layout->addWidget(sliderSyncInterval, 2, 1);
    layout->addWidget(labelSyncIntervalMax, 2, 2);

    setLayout(layout);
    registerField("syncSliderValue", sliderSyncInterval);
    connect(sliderSyncInterval, SIGNAL(valueChanged(int)), this, SLOT(slotSliderSyncIntervalChanged(int)));
}

void ZSSyncWizardPage::slotSliderSyncIntervalChanged(int value)
{
    if(value == 0)
    {
        labelSyncIntervalValue->setText("<b>Manual</b>");
    }
    else if(value < 60000)
    {
        int seconds = value / 1000;
        labelSyncIntervalValue->setText("<b>" + QString::number(seconds) + " Seconds</b>");
    }
    else
    {
        int minutes = value / 60000;
        int milliseconds = value % 60000;
        int seconds = milliseconds / 1000;

        if(seconds > 0)
        {
            if(minutes == 1)
            {
                labelSyncIntervalValue->setText("<b>" + QString::number(minutes) + " Minute, " + QString::number(seconds) + " Seconds</b>");
            }
            else
            {
                labelSyncIntervalValue->setText("<b>" + QString::number(minutes) + " Minutes, " + QString::number(seconds) + " Seconds</b>");
            }
        }
        else
        {
            if(minutes == 1)
            {
                labelSyncIntervalValue->setText("<b>" + QString::number(minutes) + " Minute</b>");
            }
            else
            {
                labelSyncIntervalValue->setText("<b>" + QString::number(minutes) + " Minutes</b>");
            }
        }
    }
}
