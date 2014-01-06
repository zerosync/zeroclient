/* =========================================================================
   MainWindow - Main user interface class of ZeroSync desktop client


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
#include "zsfilesystemwatcher.h"
#include "zsdatabase.h"
#include "zsindex.h"
#include "zssetupwizard.h"
#include "zssettings.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    ZSFileSystemWatcher *fileSystemWatcher;
    ZSDatabase *database;
    ZSIndex *index;
    ZSSettings *settings;
    ZSSetupWizard *setupWizard;

    void establishUiConnections();
    void createTrayIcon();
    void closeEvent(QCloseEvent *);

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *openTrayMenuAction;
    QAction *closeTrayMenuAction;
    QAction *muteTrayMenuAction;
    QAction *syncTrayMenuAction;
    QTimer *timer;
    bool gotWindowsMinimizedThisSession;

signals:


private slots:
    void slotClickOnTrayIcon(QSystemTrayIcon::ActivationReason);
    void slotSetZeroSyncDirectory();
    void slotFileChangeRecognized(QString);
    void slotDirectoryChangeRecognized(QString);
    void slotSaveSettings();
    void slotResetSettings();
    void slotWizardFinished();
    void slotSliderSyncIntervalChanged(int);

};

#endif // MAINWINDOW_H
