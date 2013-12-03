#ifndef ZSSETUPWIZARD_H
#define ZSSETUPWIZARD_H

#include <QObject>
#include <QWizard>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QWizardPage>
#include <QGridLayout>

class ZSSetupWizard : public QObject
{
    Q_OBJECT
public:
    explicit ZSSetupWizard(QObject *parent = 0);

private:
    QWizard wizard;
    QWizardPage* createIntroPage();
    QWizardPage* createDirectorySettingsPage();
    QWizardPage* createSyncOptionsPage();
    QWizardPage* createConclusionPage();



signals:

public slots:

};

#endif // ZSSETUPWIZARD_H
