#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowIcon(QIcon(":/images/resources/images/interact.ico") );
    ui->setupUi(this);

    database = new ZSDatabase();
    fileSystemWatcher = new ZSFileSystemWatcher(this, database);

    gotWindowsMinimizedThisSession = false;

    createTrayIcon();

    QDir directoryOfIndexFile("");
    directoryOfIndexFile.mkpath(QStandardPaths::standardLocations(QStandardPaths::DataLocation).at(0));

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
    connect(ui->buttonAddDirectory, SIGNAL(clicked()), this, SLOT(slotSetZeroSyncDirectory()));
    connect(fileSystemWatcher, SIGNAL(signalDirectoryChangeRecognized(QString)), this, SLOT(slotDirectoryChangeRecognized(QString)));
    connect(fileSystemWatcher, SIGNAL(signalFileChangeRecognized(QString)), this, SLOT(slotFileChangeRecognized(QString)));
}


void MainWindow::createTrayIcon()
{
    openTrayMenuAction = new QAction("Options", this);
    closeTrayMenuAction = new QAction("Quit", this);

    muteTrayMenuAction = new QAction("Mute Notifications", this);
    muteTrayMenuAction->setCheckable(true);
    muteTrayMenuAction->setChecked(false);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(openTrayMenuAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(muteTrayMenuAction);
    trayIconMenu->addSeparator();
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
    QDir checkDirectoryToWatch(directoryPath);

    if(directoryPath.length() > 0 && checkDirectoryToWatch.exists())
    {
        ui->labelZeroSyncDirectory->setText(directoryPath);
        fileSystemWatcher->setZeroSyncDirectory(directoryPath);
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
    if (trayIcon->isVisible())
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
