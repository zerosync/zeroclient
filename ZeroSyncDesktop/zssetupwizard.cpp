#include "zssetupwizard.h"

ZSSetupWizard::ZSSetupWizard(ZSSettings *zssettings) :
    QWizard(0)
{
    settings = zssettings;
    syncOptionsPage = new ZSSyncWizardPage();
    directorySettingsPage = new ZSDirectoryWizardPage();
    addPage(createIntroPage());
    addPage(directorySettingsPage);
    addPage(syncOptionsPage);
    addPage(createConclusionPage());
    setWindowTitle("ZeroSync Setup Wizard");
    connect(button(QWizard::FinishButton), SIGNAL(clicked()), this, SLOT(finishWizard()));
    show();
}


QWizardPage* ZSSetupWizard::createIntroPage()
{
    QWizardPage *page = new QWizardPage();
    page->setTitle("Introduction");
    QLabel *label = new QLabel("This wizard will help you setup your ZeroSync installation.");
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(label);
    page->setLayout(layout);
    return page;
}


QWizardPage* ZSSetupWizard::createConclusionPage()
{
    QWizardPage *page = new QWizardPage();
    page->setTitle("Finished");
    QLabel *label = new QLabel("You have successfully set your ZeroSync Options. Now you can start adding files and folders to your ZeroSync folder.");
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(label);
    page->setLayout(layout);
    return page;
}

void ZSSetupWizard::reject()
{
    if(QMessageBox::question( this, "ZeroSync Setup", "Setup is not complete yet. Are you sure you want to quit setup?", QMessageBox::Yes, QMessageBox::No ) == QMessageBox::Yes)
    {
        exit(0);
    }
}

void ZSSetupWizard::finishWizard()
{
    QString zsDirectory(field("pathLineEdit").toString());
    int zsSyncInterval = field("syncRadioButton").toInt();

    settings->setZeroSyncDirectory(zsDirectory);
    settings->setSyncInterval(zsSyncInterval);
}
