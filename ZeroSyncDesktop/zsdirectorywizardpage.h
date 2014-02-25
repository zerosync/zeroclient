/* =========================================================================
   ZSDirectoryWizardPage - This wizardpage is part of the setup wizard
   to configure the ZeroSync desktop client

   -------------------------------------------------------------------------
   Copyright (c) 2014 Tommy Bluhm
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


#ifndef ZSDIRECTORYWIZARDPAGE_H
#define ZSDIRECTORYWIZARDPAGE_H

#include <QObject>
#include <QWizardPage>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QDir>
#include <QFileDialog>
#include <QtDebug>
#include <QMessageBox>


//!  Class that provides an wizardpage to configure ZeroSync directory options
/*!
  Is used by the class ZSSetupWizard and provides a setup page to configure the ZeroSync
  directory where all files will be synchronized between clients.
*/
class ZSDirectoryWizardPage : public QWizardPage
{
    Q_OBJECT

public:
    //!  Constructor
    /*!
      The default constructor.
    */
    explicit ZSDirectoryWizardPage();

private:
    //!  DirectoryEdit
    /*!
      LineEdit that is used to hold the directory path.
    */
    QLineEdit *zsDirectoryEdit;

    //!  PushButtonForFiles
    /*!
      Pushbutton that opens the directory chooser.
    */
    QPushButton *zsDirectoryChooser;

    //!  GridLayout
    /*!
      The layout for the gui elements.
    */
    QGridLayout *layout;

    //!  IsComplete-Method
    /*!
      Method that checks if the selected directory exists. If not, the wizard cannot be continued unless a correct folder is set.
    */
    bool isComplete() const;

signals:

public slots:

private slots:
    //!  ZeroSyncDirectory-Slot
    /*!
      This slot is used when the ZeroSync-Directory is changed.
    */
    void slotSetZeroSyncDirectory();

};

#endif // ZSDIRECTORYWIZARDPAGE_H
