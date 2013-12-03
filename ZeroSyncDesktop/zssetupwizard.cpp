#include "zssetupwizard.h"

ZSSetupWizard::ZSSetupWizard(QObject *parent) :
    QObject(parent),
    wizard()
{
    wizard.addPage(createIntroPage());
    wizard.addPage(createDirectorySettingsPage());
    wizard.addPage(createSyncOptionsPage());
    wizard.addPage(createConclusionPage());
    wizard.setWindowTitle("ZeroSync Setup Wizard");
    wizard.show();
}


QWizardPage* ZSSetupWizard::createIntroPage()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle("Introduction");
    QLabel *label = new QLabel("This wizard will help you setup your ZeroSync installation.");
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);
    return page;
}

QWizardPage* ZSSetupWizard::createDirectorySettingsPage()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle("Registration");
    page->setSubTitle("Please fill both fields.");
    QLabel *nameLabel = new QLabel("Name:");
    QLineEdit *nameLineEdit = new QLineEdit;
    QLabel *emailLabel = new QLabel("Email address:");
    QLineEdit *emailLineEdit = new QLineEdit;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(emailLabel, 1, 0);
    layout->addWidget(emailLineEdit, 1, 1);
    page->setLayout(layout);
    return page;
}

QWizardPage* ZSSetupWizard::createSyncOptionsPage()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle("Registration");
    page->setSubTitle("Please fill both fields.");
    QLabel *nameLabel = new QLabel("Name:");
    QLineEdit *nameLineEdit = new QLineEdit;
    QLabel *emailLabel = new QLabel("Email address:");
    QLineEdit *emailLineEdit = new QLineEdit;
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(emailLabel, 1, 0);
    layout->addWidget(emailLineEdit, 1, 1);
    page->setLayout(layout);
    return page;
}

QWizardPage* ZSSetupWizard::createConclusionPage()
{
    QWizardPage *page = new QWizardPage;
    page->setTitle("Conclusion");
    QLabel *label = new QLabel("You have successfully set your ZeroSync Options. Now you can start adding files and folders to your ZeroSync folder.");
    label->setWordWrap(true);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    page->setLayout(layout);
    return page;
}
