#ifndef ZSWEBSOCKETSERVER_H
#define ZSWEBSOCKETSERVER_H

#include <QObject>
#include <QThread>
#include <QtDebug>
#include <nopoll.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>
#include "zssettings.h"

#define CMD_SIZE 4

class ZSwebsocketServer : public QThread
{
    Q_OBJECT

public:
    explicit ZSwebsocketServer(QObject *parent = 0);
    void run() Q_DECL_OVERRIDE;
    nopoll_bool on_connection_opened (noPollCtx * ctx, noPollConn * conn, noPollPtr user_data);
    void handleMsg (noPollCtx *ctx, noPollConn *con, noPollMsg *msg, noPollPtr *user_data);

signals:

private:
    ZSSettings *settings;
    QString path;
    bool fileIncome = false;
    uint32_t size_count_total = 0;
    uint32_t msg_size_total = 0;
    char *fName;


public slots:

};

#endif // ZSWEBSOCKETSERVER_H
