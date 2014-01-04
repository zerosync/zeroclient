#ifndef ZSSETUPWIZARD_H
#define ZSSETUPWIZARD_H

#include <QObject>
#include <QWizard>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QWizardPage>
#include <QGridLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QDir>
#include <QtDebug>
#include <QRadioButton>
#include "zssettings.h"
#include "zssyncwizardpage.h"
#include "zsdirectorywizardpage.h"


class ZSSetupWizard : public QWizard
{
    Q_OBJECT
public:
    explicit ZSSetupWizard(ZSSettings *zssettings = 0);

private:
    ZSSettings* settings;
    QWizardPage* createIntroPage();
    ZSDirectoryWizardPage* directorySettingsPage;
    ZSSyncWizardPage* syncOptionsPage;
    QWizardPage* createConclusionPage();
    void reject();

signals:
    void signalWizardFinished();

public slots:

private slots:
    void finishWizard();

};

#endif // ZSSETUPWIZARD_H
