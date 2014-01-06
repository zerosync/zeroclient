/* =========================================================================
   ZSDirectoryWizardPage - This wizardpage is part of the setup wizard
   to configure the ZeroSync desktop client

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


#include "zsdirectorywizardpage.h"

ZSDirectoryWizardPage::ZSDirectoryWizardPage() :
    QWizardPage()
{
    this->setTitle("Setting the ZeroSync directory");
    this->setSubTitle("All files in this directory will be synchronized with other peers.");
    zsDirectoryEdit = new QLineEdit();
    zsDirectoryChooser = new QPushButton("Choose Folder");
    layout = new QGridLayout();
    layout->addWidget(zsDirectoryEdit, 0, 0);
    layout->addWidget(zsDirectoryChooser, 0, 1);
    this->setLayout(layout);
    connect(zsDirectoryChooser, SIGNAL(clicked()), this, SLOT(slotSetZeroSyncDirectory()));
    connect(zsDirectoryEdit, SIGNAL(textChanged(QString)), this, SIGNAL(completeChanged()));
    this->registerField("pathLineEdit*", zsDirectoryEdit);
}


void ZSDirectoryWizardPage::slotSetZeroSyncDirectory()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, "Open Directory", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    zsDirectoryEdit->setText(directoryPath);
}

bool ZSDirectoryWizardPage::isComplete() const
{
    QDir checkDirectory(zsDirectoryEdit->text());
    if(zsDirectoryEdit->text().length() > 0 && checkDirectory.exists())
    {
        return true;
    }
    return false;
}
