#include "zssyncwizardpage.h"

ZSSyncWizardPage::ZSSyncWizardPage() :
    QWizardPage()
{
    setTitle("Setting the synchronization options");
    setSubTitle("Here can you set your preferred options.");

    syncIntervalLabel = new QLabel("Synchronization interval:");
    layout = new QGridLayout;
    radioButtonGroup = new QButtonGroup();
    radioButtonGroup->setExclusive(true);

    radioButtonManual = new QRadioButton();
    radioButton15Sec = new QRadioButton();
    radioButton1Min = new QRadioButton();
    radioButton5Min = new QRadioButton();
    abstractSliderToHoldValue = new QAbstractSlider();
    abstractSliderToHoldValue->setMinimum(0);
    abstractSliderToHoldValue->setMaximum(300000);

    radioButtonManual->setChecked(true);
    abstractSliderToHoldValue->setValue(0);

    radioButtonManual->setText("Manual");
    radioButton15Sec->setText("15 Seconds");
    radioButton1Min->setText("1 Minute");
    radioButton5Min->setText("5 Minutes");

    radioButtonGroup->addButton(radioButtonManual, 0);
    radioButtonGroup->addButton(radioButton15Sec, 15000);
    radioButtonGroup->addButton(radioButton1Min, 60000);
    radioButtonGroup->addButton(radioButton5Min, 300000);

    layout->addWidget(syncIntervalLabel, 0, 0);
    layout->addWidget(radioButtonManual, 1, 0);
    layout->addWidget(radioButton15Sec, 1, 1);
    layout->addWidget(radioButton1Min, 2, 0);
    layout->addWidget(radioButton5Min, 2, 1);
    setLayout(layout);
    registerField("syncRadioButton", abstractSliderToHoldValue);
    connect(radioButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(slotSetRadioButtonChecked(int)));
}

void ZSSyncWizardPage::slotSetRadioButtonChecked(int id)
{
    abstractSliderToHoldValue->setValue(id);
}
