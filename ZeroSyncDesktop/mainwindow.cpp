#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowIcon(QIcon(":/images/resources/images/interact.ico") );
    ui->setupUi(this);

    database = new ZSDatabase(this);
    fileSystemWatcher = new ZSFileSystemWatcher(this, database);
    index = new ZSIndex(this, database);
    settings = new ZSSettings(this);
    if(!settings->existSettings())
    {
        setupWizard = new ZSSetupWizard(settings);
    }
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

    radioButtonGroup = new QButtonGroup();
    radioButtonGroup->addButton(ui->radioButtonManual, 0);
    radioButtonGroup->addButton(ui->radioButton15Sec, 15000);
    radioButtonGroup->addButton(ui->radioButton1Min, 60000);
    radioButtonGroup->addButton(ui->radioButton5Min, 300000);
    radioButtonGroup->setExclusive(true);

    int interval = settings->getSyncInterval();
    if(interval == 0)
    {
        ui->radioButtonManual->setChecked(true);
    }
    else if(interval == 15000)
    {
        ui->radioButton15Sec->setChecked(true);
    }
    else if(interval == 60000)
    {
        ui->radioButton1Min->setChecked(true);
    }
    else
    {
        ui->radioButton5Min->setChecked(true);
    }

    ui->lineEditDirectoryPath->setText(settings->getZeroSyncDirectory());

    establishUiConnections();
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
}

void MainWindow::slotSaveSettings()
{
    QDir checkDirectory(ui->lineEditDirectoryPath->text());
    if(ui->lineEditDirectoryPath->text().length() > 0 && checkDirectory.exists())
    {
        settings->setZeroSyncDirectory(ui->lineEditDirectoryPath->text());
    }
    else
    {
        ui->lineEditDirectoryPath->setText(settings->getZeroSyncDirectory());
        QMessageBox::warning(0, "ZeroSync", "Settings could not be saved. Please create or choose a correct folder!", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    if(radioButtonGroup->checkedId() >= 0)
    {
        settings->setSyncInterval(radioButtonGroup->checkedId());
    }
    else
    {
        QMessageBox::warning(0, "ZeroSync", "Settings could not be saved. Please choose a sync interval!", QMessageBox::Ok, QMessageBox::Ok);
        return;
    }
    hide();
}

void MainWindow::slotResetSettings()
{
    int interval = settings->getSyncInterval();
    if(interval == 0)
    {
        ui->radioButtonManual->setChecked(true);
    }
    else if(interval == 15000)
    {
        ui->radioButton15Sec->setChecked(true);
    }
    else if(interval == 60000)
    {
        ui->radioButton1Min->setChecked(true);
    }
    else
    {
        ui->radioButton5Min->setChecked(true);
    }
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
    QDir checkDirectory(directoryPath);

    if(directoryPath.length() > 0 && checkDirectory.exists())
    {
        ui->lineEditDirectoryPath->setText(directoryPath);
    }
    else
    {
        ui->lineEditDirectoryPath->setText(settings->getZeroSyncDirectory());
        QMessageBox::warning(0, "ZeroSync", "Please create or choose a correct folder!", QMessageBox::Ok, QMessageBox::Ok);
    }
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
