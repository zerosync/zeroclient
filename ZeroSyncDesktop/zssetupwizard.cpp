#include "zssetupwizard.h"

ZSSetupWizard::ZSSetupWizard(QObject *parent, ZSSettings *zssettings) :
    QObject(parent),
    wizard()
{
    settings = zssettings;
    syncOptionsPage = new ZSSyncWizardPage();
    directorySettingsPage = new ZSDirectoryWizardPage();
    wizard.addPage(createIntroPage());
    wizard.addPage(directorySettingsPage);
    wizard.addPage(syncOptionsPage);
    wizard.addPage(createConclusionPage());
    wizard.setWindowTitle("ZeroSync Setup Wizard");
    wizard.show();
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
