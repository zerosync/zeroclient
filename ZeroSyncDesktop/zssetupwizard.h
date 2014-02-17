/* =========================================================================
   ZSSetupWizard - Setup wizard class for the ZeroSync desktop client


   -------------------------------------------------------------------------
   Copyright (c) 2013 Tommy Bluhm
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


//!  Class that provides a setup wizard for the ZeroSync desktop client.
/*!
  When the user starts ZeroSync for the first time an instance of ZSSetupWizard will
  start. This setup wizard is used to set the ZeroSync folder and the preferred
  synchronization options. It has to be finished in order to use ZeroSync.
  When the wizard gets aborted, ZeroSync quits and the next time the user starts
  ZeroSync, the setup wizard will start again.
*/
class ZSSetupWizard : public QWizard
{
    Q_OBJECT
public:
    explicit ZSSetupWizard();

private:
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
