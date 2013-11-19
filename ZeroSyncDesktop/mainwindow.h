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
#include "zsfilesystemwatcher.h"
#include "zsdatabase.h"
#include "zsindex.h"

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

    void establishUiConnections();
    void createTrayIcon();
    void closeEvent(QCloseEvent *);

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *openTrayMenuAction;
    QAction *closeTrayMenuAction;
    QAction *muteTrayMenuAction;

    bool gotWindowsMinimizedThisSession;

signals:


private slots:
    void slotClickOnTrayIcon(QSystemTrayIcon::ActivationReason);
    void slotSetZeroSyncDirectory();
    void slotFileChangeRecognized(QString);
    void slotDirectoryChangeRecognized(QString);

};

#endif // MAINWINDOW_H
