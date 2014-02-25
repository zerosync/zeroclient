/* =========================================================================
   MainWindow - Main user interface class of ZeroSync desktop client


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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>
#include <iostream>
#include <QFileDialog>
#include <QtDebug>
#include <QMessageBox>
#include <QTimer>
#include <QButtonGroup>
#include <QDesktopServices>
#include "zsfilesystemwatcher.h"
#include "zsdatabase.h"
#include "zsindex.h"
#include "zssetupwizard.h"
#include "zssettings.h"
#include "zsconnector.h"
#include "zshtmlbuilder.h"
#include "zsinotify.h"


namespace Ui {
    class MainWindow;
}

//!  Class that provides the ZeroSync user interface
/*!
  This class provides the ZeroSync user interface including the tray icon and the
  setup window.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //!  Constructor
    /*!
      The default constructor.
    */
    explicit MainWindow(QWidget *parent = 0);

    //!  Deconstructor
    /*!
      The default deconstructor.
    */
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //!  The ZeroSync FileSystemWatcher
    /*!
      The FileSystemWatcher is used to watch the local filesystem for changes that will be written to the local ZeroSync database.
    */
    ZSFileSystemWatcher *fileSystemWatcher;

    //!  The ZeroSync Index
    /*!
      The index is used to write local filesystem changes to the persistent index that is shared between clients.
    */
    ZSIndex *index;

    //!  The ZeroSync SetupWizard
    /*!
      The setup wizard is used to set up the ZeroSync options.
    */
    ZSSetupWizard *setupWizard;

    //!  The ZeroSync Connector
    /*!
      The connector is used to establish connections between clients with the ZeroSync protocol.
    */
    ZSConnector *connector;

    //!  The ZeroSync HTMLBuilder
    /*!
      The html builder is used to build the ZeroSyncWebIndex html file.
    */
    ZShtmlBuilder *htmlBuilder;

    //!  ZSNotify
    /*!
      This class is used to implement some inotify specific functionalities.
    */
    ZSInotify *inotify;

    //!  Method to establish UI-Connections
    /*!
      This method is used to establish most of the signal-slot-connections within the mainwindow class.
    */
    void establishUiConnections();

    //!  Method to create the tray icon
    /*!
      This method is used to create the tray icon that is shown at the task bar of the operating system.
    */
    void createTrayIcon();

    //!  Overwritten CloseEvent-Method
    /*!
      This method is used to change the behavior when trying to close ZeroSync.
    */
    void closeEvent(QCloseEvent *);

    //!  The QSystemTrayIcon Object
    /*!
      Is used to set the icon for the tray menu of ZeroSync.
    */
    QSystemTrayIcon *trayIcon;

    //!  The TrayIcon Menu
    /*!
      Is used as the menu that will be shown when user clicks on the tray icon.
    */
    QMenu *trayIconMenu;

    //!  Open-MenuAction
    /*!
      Is used when user clicks on "Open" in the trayicon menu.
    */
    QAction *openTrayMenuAction;

    //!  Close-MenuAction
    /*!
      Is used when user clicks on "Close" in the trayicon menu.
    */
    QAction *closeTrayMenuAction;

    //!  Mute-MenuAction
    /*!
      Is used when user clicks on "Mute notifications" in the trayicon menu.
    */
    QAction *muteTrayMenuAction;

    //!  Sync-MenuAction
    /*!
      Is used when user clicks on "Synchronize" in the trayicon menu.
    */
    QAction *syncTrayMenuAction;

    //!  HTML-MenuAction
    /*!
      Is used when user clicks on "Open ZeroWebIndex" in the trayicon menu.
    */
    QAction *htmlTrayMenuAction;

    //!  Synchronization-Timer
    /*!
      This timer is used to synchronize ZeroSync periodically.
    */
    QTimer *timer;

    //!  Minimization-Check
    /*!
      This boolean is used to check if ZeroSync got minimized in this session yet.
    */
    bool gotWindowsMinimizedThisSession;

signals:

private slots:
    //!  TrayiconClick-Slot
    /*!
      This slot is used when the user clicks on the Zerosync tray icon.
    */
    void slotClickOnTrayIcon(QSystemTrayIcon::ActivationReason);

    //!  ZeroSyncDirectory-Slot
    /*!
      This slot is used when the ZeroSync-Directory is changed.
    */
    void slotSetZeroSyncDirectory();

    //!  Filechange-Slot
    /*!
      This slot is used to show with a notification that a file got changed.
    */
    void slotFileChangeRecognized(QString);

    //! Directorychange-Slot
    /*!
      This slot is used to show with a notification that a directory got changed.
    */
    void slotDirectoryChangeRecognized(QString);

    //!  SaveSettings-Slot
    /*!
      This slot is used when the user saves settings in the option window.
    */
    void slotSaveSettings();

    //!  ResetSettings-Slot
    /*!
      This slot is used when the user resets the settings in the option window.
    */
    void slotResetSettings();

    //!  WizardFinished-Slot
    /*!
      This slot is used when the user finishes the setup wizard successfully.
    */
    void slotWizardFinished();

    //!  IntervalChange-Slot
    /*!
      This slot is used when the user changes the synchronization interval in the option window.
    */
    void slotSliderSyncIntervalChanged(int);

    //!  ZeroWebIndex-Slot
    /*!
      This slot is used when the user opens the ZeroWebIndex with the tray icon menu.
    */
    void slotOpenZeroWebIndex();

};

#endif // MAINWINDOW_H
