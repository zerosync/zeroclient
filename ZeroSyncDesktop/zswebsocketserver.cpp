#include "zswebsocketserver.h"

ZSwebsocketServer::ZSwebsocketServer(QObject *parent) :
    QThread(parent)
{
    zspath = ZSSettings::getInstance()->getZeroSyncDirectory();

    qDebug() << "Path check: ";
    qDebug() << zspath;
}

ZSwebsocketServer::~ZSwebsocketServer() {
    qDebug() << "Killed server process!";
    proc->terminate();
    delete proc;
}

void ZSwebsocketServer::run ()
{
    /*
    //QString compiling_server = "../../zeroweb/src/make";
    QString compiling_server = "/home/burne/Dropbox/Me/Studium/Semester5/Wahlprojekt/Cloudfolder/zeroweb/src/make";

    QProcess *compile_proc = new QProcess();

    compile_proc->execute(compiling_server);
    qDebug() << "Error: ";
    qDebug() << compile_proc->errorString();
    qDebug() << "State: ";
    qDebug() << compile_proc->state();
*/
    proc = new QProcess();

    QString server = "/home/burne/Dropbox/Me/Studium/Semester5/Wahlprojekt/Cloudfolder/zeroweb/src/server";

    QStringList args;
    args << zspath;

    proc->start(server, args);
}
