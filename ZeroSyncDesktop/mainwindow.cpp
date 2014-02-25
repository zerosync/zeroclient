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


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowIcon(QIcon(":/images/resources/images/interact.ico") );
    ui->setupUi(this);

    if(!ZSSettings::getInstance()->existSettings())
    {
        qDebug() << "Information - MainWindow::MainWindow(QWidget *parent) - ZeroSync is starting for the first time...executing setup wizard";
        setupWizard = new ZSSetupWizard();
        connect(setupWizard, SIGNAL(signalWizardFinished()), this, SLOT(slotWizardFinished()));
    }
    else
    {
        slotWizardFinished();

    }
}


MainWindow::~MainWindow()
{
    delete ui;
    delete openTrayMenuAction;
    delete closeTrayMenuAction;
    delete trayIcon;
    delete trayIconMenu;
    server->terminate();
}


void MainWindow::establishUiConnections()
{
    connect(openTrayMenuAction, SIGNAL(triggered()), this, SLOT(show()));
    connect(closeTrayMenuAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->actionQuitZeroSync, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slotClickOnTrayIcon(QSystemTrayIcon::ActivationReason)));
    connect(ui->buttonSetDirectory, SIGNAL(clicked()), this, SLOT(slotSetZeroSyncDirectory()));
    connect(fileSystemWatcher, SIGNAL(signalDirectoryChangeRecognized(QString)), this, SLOT(slotDirectoryChangeRecognized(QString)));
    connect(fileSystemWatcher, SIGNAL(signalFileChangeRecognized(QString)), this, SLOT(slotFileChangeRecognized(QString)));
    connect(ui->buttonSave, SIGNAL(clicked()), this, SLOT(slotSaveSettings()));
    connect(ui->buttonReset, SIGNAL(clicked()), this, SLOT(slotResetSettings()));
    connect(syncTrayMenuAction, SIGNAL(triggered()), index, SLOT(slotUpdateIndex()));
    connect(ui->sliderSyncInterval, SIGNAL(valueChanged(int)), this, SLOT(slotSliderSyncIntervalChanged(int)));
    connect(fileSystemWatcher, SIGNAL(signalDirectoryChangeRecognized(QString)), htmlBuilder, SLOT(slotGenerateHtml()));
    connect(fileSystemWatcher, SIGNAL(signalFileChangeRecognized(QString)), htmlBuilder, SLOT(slotGenerateHtml()));
    connect(index, SIGNAL(signalIndexUpdated(int)), connector, SLOT(slotSynchronizeUpdate(int)));
    connect(htmlTrayMenuAction, SIGNAL(triggered()), this, SLOT(slotOpenZeroWebIndex()));
}

void MainWindow::slotSaveSettings()
{
    QDir checkDirectory(ui->lineEditDirectoryPath->text());
    if(ui->lineEditDirectoryPath->text().length() > 0 && checkDirectory.exists())
    {
        if(ZSSettings::getInstance()->getZeroSyncDirectory() != ui->lineEditDirectoryPath->text())
        {
            ZSSettings::getInstance()->setZeroSyncDirectory(ui->lineEditDirectoryPath->text());
            fileSystemWatcher->changeZeroSyncDirectory(ZSSettings::getInstance()->getZeroSyncDirectory());
            qDebug() << "Information - MainWindow::slotSaveSettings() - ZeroSync folder changed: " << ui->lineEditDirectoryPath->text();
        }
        if(ZSSettings::getInstance()->getSyncInterval() != ui->sliderSyncInterval->value())
        {
            ZSSettings::getInstance()->setSyncInterval(ui->sliderSyncInterval->value());
            timer->stop();
            if(ZSSettings::getInstance()->getSyncInterval() > 0)
            {
                index->slotUpdateIndex();
                timer->start(ZSSettings::getInstance()->getSyncInterval());
            }
            qDebug() << "Information - MainWindow::slotSaveSettings() - Synchronization interval changed: " << ui->sliderSyncInterval->value();
        }
    }
    else
    {
        ui->lineEditDirectoryPath->setText(ZSSettings::getInstance()->getZeroSyncDirectory());
        ui->sliderSyncInterval->setValue(ZSSettings::getInstance()->getSyncInterval());
        QMessageBox::warning(0, "ZeroSync", "Settings could not be saved. Please create or choose a correct folder!", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    hide();
}

void MainWindow::slotOpenZeroWebIndex()
{
    QDesktopServices::openUrl(QUrl("../ZeroWebIndex.html", QUrl::TolerantMode));
}

void MainWindow::slotResetSettings()
{
    ui->sliderSyncInterval->setValue(ZSSettings::getInstance()->getSyncInterval());
    ui->lineEditDirectoryPath->setText(ZSSettings::getInstance()->getZeroSyncDirectory());
}

void MainWindow::createTrayIcon()
{
    syncTrayMenuAction = new QAction("Synchronize", this);
    openTrayMenuAction = new QAction("Options", this);
    closeTrayMenuAction = new QAction("Quit", this);
    htmlTrayMenuAction = new QAction("Open ZeroWebIndex", this);

    muteTrayMenuAction = new QAction("Mute Notifications", this);
    muteTrayMenuAction->setCheckable(true);
    muteTrayMenuAction->setChecked(false);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(syncTrayMenuAction);
    trayIconMenu->addAction(htmlTrayMenuAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(openTrayMenuAction);
    trayIconMenu->addAction(muteTrayMenuAction);
    trayIconMenu->addAction(closeTrayMenuAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/images/resources/images/interact.png"));
    trayIcon->show();
}


void MainWindow::slotClickOnTrayIcon(QSystemTrayIcon::ActivationReason activationReason)
{
    if(activationReason == QSystemTrayIcon::Trigger)
    {
        this->show();
    }
}


void MainWindow::slotSetZeroSyncDirectory()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, "Open Directory", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->lineEditDirectoryPath->setText(directoryPath);
}


void MainWindow::slotFileChangeRecognized(QString pathToFile)
{
    if(!muteTrayMenuAction->isChecked())
    {
        trayIcon->showMessage("ZeroSync", "File change recognized:\n" + pathToFile, QSystemTrayIcon::Information, 10000);
    }

}


void MainWindow::slotDirectoryChangeRecognized(QString pathToDirectory)
{
    if(!muteTrayMenuAction->isChecked())
    {
        trayIcon->showMessage("ZeroSync", "Directory change recognized:\n" + pathToDirectory, QSystemTrayIcon::Information, 10000);
    }
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if(trayIcon->isVisible())
    {
        if(!gotWindowsMinimizedThisSession && !muteTrayMenuAction->isChecked())
        {
           trayIcon->showMessage("ZeroSync", "ZeroSync is minimized to tray and will\nsynchronize your files in background.", QSystemTrayIcon::Information, 10000);
           gotWindowsMinimizedThisSession = true;
        }

        hide();
        event->ignore();
    }
}

void MainWindow::slotWizardFinished()
{
    fileSystemWatcher = new ZSFileSystemWatcher(this);
    fileSystemWatcher->setZeroSyncDirectory(ZSSettings::getInstance()->getZeroSyncDirectory());
    index = new ZSIndex(this);
    connector = new ZSConnector(this);
    htmlBuilder = new ZShtmlBuilder(this);
    //server = new ZSwebsocketServer(this);
    //server->start();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), index, SLOT(slotUpdateIndex()));

    if(ZSSettings::getInstance()->getSyncInterval() > 0)
    {
        index->slotUpdateIndex();
        timer->start(ZSSettings::getInstance()->getSyncInterval());
    }
    gotWindowsMinimizedThisSession = false;

    createTrayIcon();

    QDir directoryOfIndexFile("");
    directoryOfIndexFile.mkpath(QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0));

    ui->sliderSyncInterval->setValue(ZSSettings::getInstance()->getSyncInterval());
    slotSliderSyncIntervalChanged(ZSSettings::getInstance()->getSyncInterval());
    ui->lineEditDirectoryPath->setText(ZSSettings::getInstance()->getZeroSyncDirectory());

    establishUiConnections();
}

void MainWindow::slotSliderSyncIntervalChanged(int value)
{
    if(value == 0)
    {
        ui->labelSyncIntervalValue->setText("<b>Manual</b>");
    }
    else if(value < 60000)
    {
        int seconds = value / 1000;
        ui->labelSyncIntervalValue->setText("<b>" + QString::number(seconds) + " Seconds</b>");
    }
    else
    {
        int minutes = value / 60000;
        int milliseconds = value % 60000;
        int seconds = milliseconds / 1000;
        if(seconds > 0)
        {
            if(minutes == 1)
            {
                ui->labelSyncIntervalValue->setText("<b>" + QString::number(minutes) + " Minute, " + QString::number(seconds) + " Seconds</b>");
            }
            else
            {
                ui->labelSyncIntervalValue->setText("<b>" + QString::number(minutes) + " Minutes, " + QString::number(seconds) + " Seconds</b>");
            }
        }
        else
        {
            if(minutes == 1)
            {
                ui->labelSyncIntervalValue->setText("<b>" + QString::number(minutes) + " Minute</b>");
            }
            else
            {
                ui->labelSyncIntervalValue->setText("<b>" + QString::number(minutes) + " Minutes</b>");
            }
        }
    }
}
