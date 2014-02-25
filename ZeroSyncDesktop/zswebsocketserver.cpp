#include "zswebsocketserver.h"

/**
 * @brief ZSwebsocketServer::ZSwebsocketServer  constructor of the ZSwebsocketServer class. It gets an instance of the Settings to parse the
 *                                              directory which is wachted.
 * @param parent fathers process
 */
ZSwebsocketServer::ZSwebsocketServer(QObject *parent) :
    QThread(parent)
{
    zspath = ZSSettings::getInstance()->getZeroSyncDirectory();

    qDebug() << "Path check: ";
    qDebug() << zspath;
}

/**
 * @brief ZSwebsocketServer::~ZSwebsocketServer the destructor kills the server process, which is started externly.
 */
ZSwebsocketServer::~ZSwebsocketServer() {
    qDebug() << "Killed server process!";
    proc->terminate();
    delete proc;
}

/**
 * @brief ZSwebsocketServer::run is the overwritten thread running function. There starts the websocket server process.
 */
void ZSwebsocketServer::run ()
{
    proc = new QProcess();

    QString server = "../server";

    QFile file("../server");
    if (!file.exists()) {
        qDebug() << "Sorry u haven´t the required server file, to start the WebSocket Server. HTML funtions, like upload, delete or Download are disabled.";
        return;
    }

    QStringList args;
    args << zspath;

    proc->start(server, args);
}
