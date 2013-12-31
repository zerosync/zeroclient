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


class ZSSetupWizard : public QObject
{
    Q_OBJECT
public:
    explicit ZSSetupWizard(QObject *parent = 0, ZSSettings *zssettings = 0);

private:
    ZSSettings* settings;
    QWizard wizard;
    QWizardPage* createIntroPage();
    ZSDirectoryWizardPage* directorySettingsPage;
    ZSSyncWizardPage* syncOptionsPage;
    QWizardPage* createConclusionPage();

signals:

public slots:

};

#endif // ZSSETUPWIZARD_H
