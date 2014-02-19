#ifndef ZSCONSOLEWINDOW_H
#define ZSCONSOLEWINDOW_H

#include <QObject>
#include <QTimer>
#include "zsfilesystemwatcher.h"
#include "zsdatabase.h"
#include "zsindex.h"
#include "zssetupwizard.h"
#include "zssettings.h"
#include "zsconnector.h"
#include "zshtmlbuilder.h"
#include "zsinotify.h"


class ZSConsoleWindow : public QObject
{
    Q_OBJECT
public:
    explicit ZSConsoleWindow(QObject *parent = 0, bool newDirectory = false);

private:
    ZSFileSystemWatcher *fileSystemWatcher;
    ZSIndex *index;
    ZSSetupWizard *setupWizard;
    ZSConnector *connector;
    ZShtmlBuilder *htmlBuilder;
    ZSInotify *inotify;
    QTimer *timer;

signals:

public slots:

};

#endif // ZSCONSOLEWINDOW_H
