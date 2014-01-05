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
