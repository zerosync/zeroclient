#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>
#include <iostream>
#include <QFileDialog>
#include <QtDebug>
#include "zsfilesystemwatcher.h"

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

    void establishUiConnections();
    void createTrayIcon();
    void closeEvent(QCloseEvent *);

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QAction *openTrayMenuAction;
    QAction *closeTrayMenuAction;

signals:
    void signalDirectoryRemovedFromWatchList(QString);

private slots:
    void slotClickOnTrayIcon(QSystemTrayIcon::ActivationReason);
    void slotAddDirectoryToWatchList();
    void slotRemoveDirectoryFromWatchList();

};

#endif // MAINWINDOW_H
