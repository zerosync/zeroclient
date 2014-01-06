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
    int zsSyncInterval = field("syncSliderValue").toInt();

    settings->setZeroSyncDirectory(zsDirectory);
    settings->setSyncInterval(zsSyncInterval);
    emit signalWizardFinished();
}
