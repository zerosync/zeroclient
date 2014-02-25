#ifndef ZSWEBSOCKETSERVER_H
#define ZSWEBSOCKETSERVER_H

#include <QObject>
#include <QThread>
#include <QtDebug>
#include <QProcess>
#include "zssettings.h"

#define CMD_SIZE 4

class ZSwebsocketServer : public QThread
{
    Q_OBJECT

public:
    explicit ZSwebsocketServer(QObject *parent = 0);
    ~ZSwebsocketServer();
    void run() Q_DECL_OVERRIDE;

signals:

private:
    QString zspath;
    QProcess *proc;


public slots:

};

#endif // ZSWEBSOCKETSERVER_H
