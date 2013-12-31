#include "zssyncwizardpage.h"

ZSSyncWizardPage::ZSSyncWizardPage() :
    QWizardPage()
{
    this->setTitle("Setting the synchronization options");
    this->setSubTitle("Here can you set your preferred options.");
    QLabel *syncIntervalLabel = new QLabel("Synchronization interval:");
    QGridLayout *layout = new QGridLayout;
    QRadioButton *radioButtonManual = new QRadioButton();
    QRadioButton *radioButton15Sec = new QRadioButton();
    QRadioButton *radioButton1Min = new QRadioButton();
    QRadioButton *radioButton5Min = new QRadioButton();
    radioButtonManual->setText("Manual");
    radioButton15Sec->setText("15 Seconds");
    radioButton1Min->setText("1 Minute");
    radioButton5Min->setText("5 Minutes");
    layout->addWidget(syncIntervalLabel, 0, 0);
    layout->addWidget(radioButtonManual, 1, 0);
    layout->addWidget(radioButton15Sec, 1, 1);
    layout->addWidget(radioButton1Min, 2, 0);
    layout->addWidget(radioButton5Min, 2, 1);
    this->setLayout(layout);
}
