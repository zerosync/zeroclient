#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setWindowIcon(QIcon(":/images/resources/images/interact.ico") );
    ui->setupUi(this);

    fileSystemWatcher = new ZSFileSystemWatcher();

    createTrayIcon();

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
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(slotClickOnTrayIcon(QSystemTrayIcon::ActivationReason)));
    connect(ui->buttonAddDirectory, SIGNAL(clicked()), this, SLOT(slotAddDirectoryToWatchList()));
    connect(ui->buttonRemoveDirectory, SIGNAL(clicked()), this, SLOT(slotRemoveDirectoryFromWatchList()));
    connect(this, SIGNAL(signalDirectoryRemovedFromWatchList(QString)), fileSystemWatcher, SLOT(slotDirectoryAboutToBeRemoved(QString)));
}


void MainWindow::createTrayIcon()
{
    openTrayMenuAction = new QAction("Open GUI", this);
    closeTrayMenuAction = new QAction("Quit ZeroSync", this);

    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(openTrayMenuAction);
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


void MainWindow::slotAddDirectoryToWatchList()
{
    QString directoryPath = QFileDialog::getExistingDirectory(this, "Open Directory", "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(directoryPath.length() > 0)
    {
        ui->listWidgetWatchedDirectories->addItem(directoryPath);
        fileSystemWatcher->addDirectoryToWatch(directoryPath);
    }
}


void MainWindow::slotRemoveDirectoryFromWatchList()
{
    int currentRow = ui->listWidgetWatchedDirectories->currentRow();
    if(currentRow != -1)
    {
        QListWidgetItem* item = ui->listWidgetWatchedDirectories->takeItem(currentRow);
        emit signalDirectoryRemovedFromWatchList(item->text());
        delete item;
    }
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible())
    {
        hide();
        event->ignore();
    }
}
