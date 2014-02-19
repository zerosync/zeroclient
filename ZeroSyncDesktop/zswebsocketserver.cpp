#include "zswebsocketserver.h"

ZSwebsocketServer::ZSwebsocketServer(QObject *parent) :
    QThread(parent)
{
    path = settings->getZeroSyncDirectory();
}

void ZSwebsocketServer::run ()
{
    noPollCtx *ctx = nopoll_ctx_new();
    if (!ctx) {
        qDebug() << "Could not create context. Shutting down!";
        return;
    }

    // NULL ist the default port: 80
    noPollConn *listener = nopoll_listener_new(ctx, "localhost", "1234");
    if (!nopoll_conn_is_ok(listener))  {
       qDebug() << "The listener wasn´t initilialized correctly.";
       return;
    }

    nopoll_ctx_set_on_msg(ctx, (noPollOnMessageHandler)&ZSwebsocketServer::handleMsg, NULL);
    nopoll_ctx_set_on_open(ctx, (noPollActionHandler)&ZSwebsocketServer::on_connection_opened, NULL);

    // Wait for Client Action
    nopoll_loop_wait(ctx, 0);

    qDebug() << "Close connection...";
    nopoll_conn_close(listener);
    nopoll_ctx_unref(ctx);

}

/**
  *
  *  This function checks, if the connection is established correctly. If true, the connection is finally established.
  *
  **/
nopoll_bool ZSwebsocketServer::on_connection_opened (noPollCtx * ctx, noPollConn * conn, noPollPtr user_data)
{
    if (! nopoll_conn_set_sock_block (nopoll_conn_socket (conn), nopoll_false)) {
         qDebug() << "ERROR: failed to configure non-blocking state to connection..";
         return nopoll_false;
    }

    /* check to reject */
    if (nopoll_cmp (nopoll_conn_get_origin (conn), "http://deny.aspl.es"))  {
        qDebug() << "INFO: rejected connection!";
        return nopoll_false;
    }

    /* notify connection accepted */
    qDebug() << "Connection established!";
    return nopoll_true;
}

void ZSwebsocketServer::handleMsg (noPollCtx *ctx, noPollConn *con, noPollMsg *msg, noPollPtr *user_data)
{
    unsigned long msg_size = nopoll_msg_get_payload_size(msg);
    uint8_t *clientMsg = (uint8_t *)calloc (msg_size, sizeof(uint8_t));
    clientMsg = (uint8_t *) nopoll_msg_get_payload(msg);

    if (!fileIncome) {
        qDebug() << "Start Uploading...\n";
        qDebug() << "Server received"+ QString::number(nopoll_msg_get_payload_size(msg));
        fileIncome = true;
        /* Check if the msg is the initializing CMD msg before the file msgs*/
        char tmp[CMD_SIZE];
        fName = (char *)malloc((msg_size-CMD_SIZE)*sizeof(char));
        strncpy (tmp, (char *)clientMsg, 3);
        tmp[3] = '\0';

        if (strcmp(tmp, "ZSF") == 0) { // if the cmd prefix is set in the msg, the following chars are the Name of the incoming file
            int y;
            // get uint32 from network byte order
            msg_size_total = ((uint32_t) (clientMsg [3]) << 24)
                  + ((uint32_t) (clientMsg [4]) << 16)
                  + ((uint32_t) (clientMsg [5]) << 8)
                  +  (uint32_t) (clientMsg [6]);
            for (y = 0; y < msg_size; y++){
                fName[y] = clientMsg[y+(CMD_SIZE+4-1)]; // fill the fileName in the fName string
            }
            qDebug() << "msg_size_total:"+ QString::number(msg_size_total);
            fName[strlen(fName)] = '\0';
        }/* End of checking */

    } else {
        qDebug() << "Server received size: "+ QString::number(nopoll_msg_get_payload_size(msg));
        qDebug() << "msg_size_total: "+ QString::number(msg_size_total)+ "size_count_total: "+QString::number(size_count_total);
        char *path = "/home/burne/Documents/bigFiles/testDestination/";
        char *fullPath;
        fullPath = (char *)malloc((strlen(fName)+strlen(path) + 1)*sizeof(char));
        strcpy(fullPath, path);
        strcat(fullPath, fName);

        qDebug() << "path: "+ QString(fullPath);
        FILE *file = fopen(fullPath, "a+b");
        if (file == NULL){
            qDebug() << "ERROR: Could not open the file to write!\n";
            return;
        }
        int z;
        for (z=0; z<msg_size; z++) {
            if ((fwrite(&clientMsg[z],(size_t)1,(size_t)1,file))<0) {
                qDebug() << "ERROR: Could not write to the file!\n";
                break;
            }
            size_count_total++;
            if (size_count_total == msg_size_total) {
                qDebug() << "File end reached.\n";
                free (fName);
                fileIncome = false; //finished file - grant access the next file
                msg_size_total = 0;
                size_count_total = 0;
                break;
            }
        }
        fclose (file);
        free (fullPath);
    }
}
