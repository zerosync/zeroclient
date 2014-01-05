#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowIcon(QIcon(":/images/resources/images/interact.ico") );
    ui->setupUi(this);

    settings = new ZSSettings(this);
    if(!settings->existSettings())
    {
        setupWizard = new ZSSetupWizard(settings);
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
}

void MainWindow::slotSaveSettings()
{
    QDir checkDirectory(ui->lineEditDirectoryPath->text());
    if(ui->lineEditDirectoryPath->text().length() > 0 && checkDirectory.exists())
    {
        settings->setZeroSyncDirectory(ui->lineEditDirectoryPath->text());
        fileSystemWatcher->changeZeroSyncDirectory(settings->getZeroSyncDirectory());
        settings->setSyncInterval(ui->sliderSyncInterval->value());
        timer->stop();
        if(settings->getSyncInterval() > 0)
        {
            index->slotUpdateIndex();
            timer->start(settings->getSyncInterval());
        }
    }
    else
    {
        ui->lineEditDirectoryPath->setText(settings->getZeroSyncDirectory());
        ui->sliderSyncInterval->setValue(settings->getSyncInterval());
        QMessageBox::warning(0, "ZeroSync", "Settings could not be saved. Please create or choose a correct folder!", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    hide();
}

void MainWindow::slotResetSettings()
{
    ui->sliderSyncInterval->setValue(settings->getSyncInterval());
    ui->lineEditDirectoryPath->setText(settings->getZeroSyncDirectory());
}

void MainWindow::createTrayIcon()
{
    syncTrayMenuAction = new QAction("Synchronize", this);
    openTrayMenuAction = new QAction("Options", this);
    closeTrayMenuAction = new QAction("Quit", this);

    muteTrayMenuAction = new QAction("Mute Notifications", this);
    muteTrayMenuAction->setCheckable(true);
    muteTrayMenuAction->setChecked(false);


    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(syncTrayMenuAction);
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
    database = new ZSDatabase(this);
    fileSystemWatcher = new ZSFileSystemWatcher(this, database);
    index = new ZSIndex(this, database);
    fileSystemWatcher->setZeroSyncDirectory(settings->getZeroSyncDirectory());

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), index, SLOT(slotUpdateIndex()));

    if(settings->getSyncInterval() > 0)
    {
        index->slotUpdateIndex();
        timer->start(settings->getSyncInterval());
    }
    gotWindowsMinimizedThisSession = false;

    createTrayIcon();

    QDir directoryOfIndexFile("");
    directoryOfIndexFile.mkpath(QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0));

    ui->sliderSyncInterval->setValue(settings->getSyncInterval());
    slotSliderSyncIntervalChanged(settings->getSyncInterval());
    ui->lineEditDirectoryPath->setText(settings->getZeroSyncDirectory());

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
