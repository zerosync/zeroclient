#include "zsconnector.h"

zsync_agent_t * ZSConnector::agent;

ZSConnector::ZSConnector(QObject *parent) :
    QObject(parent)
{
    ZSConnector::agent = zsync_agent_new();
    zsync_agent_set_get_update(ZSConnector::agent, (void *) &ZSConnector::get_update);
    zsync_agent_set_pass_update(ZSConnector::agent, (void *) &ZSConnector::pass_update);

    zsync_agent_set_get_chunk(ZSConnector::agent, (void *) &ZSConnector::get_chunk);
    zsync_agent_set_pass_chunk(ZSConnector::agent, (void *) &ZSConnector::pass_chunk);

    zsync_agent_set_get_current_state(ZSConnector::agent, (void *) &ZSConnector::get_current_state);

    qDebug() << zsync_agent_start(ZSConnector::agent);
}


zlist_t* ZSConnector::get_update(uint64_t from_state)
{
    qDebug() << "get_update";
    QSqlQuery query = ZSDatabase::getInstance()->fetchUpdateFromState(from_state);

    zlist_t *updateList = zlist_new();
    while (query.next()) {
        zs_fmetadata_t *fmetadata = zs_fmetadata_new();
        zs_fmetadata_set_path(fmetadata, "%s", query.value(1).toString().toLatin1().data());
        zs_fmetadata_set_timestamp(fmetadata, query.value(3).toULongLong());
        QString op = query.value(2).toString();
        if (op.compare("UPD") == 0) {
            zs_fmetadata_set_operation(fmetadata, ZS_FILE_OP_UPD);
            zs_fmetadata_set_size(fmetadata, query.value(4).toULongLong());
            zs_fmetadata_set_checksum(fmetadata, query.value(6).toULongLong());
        }
        else
        if (op.compare("REN") == 0 ) {
            zs_fmetadata_set_operation(fmetadata, ZS_FILE_OP_REN);
            zs_fmetadata_set_renamed_path(fmetadata, "%", query.value(5).toString().toLatin1().data());
        }
        else
        if (op.compare("DEL") == 0) {
            zs_fmetadata_set_operation(fmetadata, ZS_FILE_OP_DEL);
        }
        zlist_append(updateList, fmetadata);
    }
    return zlist_size(updateList) > 0 ? updateList : NULL;
}

void ZSConnector::pass_update(char* sender, zlist_t* file_metadata)
{
    qDebug() << "pass_update";
    zlist_t *requestList = zlist_new();
    uint64_t requestBytes = 0;
    zs_fmetadata_t *fmetadata = (zs_fmetadata_t *) zlist_first(file_metadata);
    while(fmetadata) {
        QString path = QString(zs_fmetadata_path(fmetadata));
        QSqlQuery query = ZSDatabase::getInstance()->fetchFileByPath(path);
        uint64_t timestamp = 0;
        if (query.next()) {
           timestamp = query.value(1).toULongLong();
        }

        switch(zs_fmetadata_operation(fmetadata)) {
        case ZS_FILE_OP_UPD:
            // Add to request list if local file is older
            // NOTE: newest file always wins == no merging
            if (timestamp <= zs_fmetadata_timestamp (fmetadata)) {
                zlist_append(requestList, zs_fmetadata_path(fmetadata));
                requestBytes += zs_fmetadata_size (fmetadata);
            }
            break;
        case ZS_FILE_OP_REN:
            if (timestamp <= zs_fmetadata_timestamp (fmetadata)) {
                // move file to new location. EXCLUDE FROM UPDATE
            }
            break;
        case ZS_FILE_OP_DEL:
            if (timestamp <= zs_fmetadata_timestamp (fmetadata)) {
                // remove file from storage. EXCLUDE FROM UPDATE
            }
            break;
        }

        // get next list entry
        fmetadata = (zs_fmetadata_t *) zlist_next(file_metadata);
    }
    zsync_agent_send_request_files(ZSConnector::agent, sender, requestList, requestBytes);
}

zchunk_t * ZSConnector::get_chunk(char *path, uint64_t chunk_size, uint64_t offset)
{
    qDebug() << "get_chunk" << path;
    char *parent = strdup (ZSSettings::getInstance()->getZeroSyncDirectory().toLatin1().data());
    zfile_t *file = zfile_new(parent, path);
    int rc = zfile_input(file);
    qDebug() << "open file" << rc;
    zchunk_t *chunk = zfile_read(file, chunk_size, offset);
    zfile_close(file);
    zfile_destroy(&file);
    return zchunk_size (chunk) > 0 ? chunk : NULL;
}

void ZSConnector::pass_chunk(zchunk_t *chunk, char *path, uint64_t sequence, uint64_t offset)
{
    qDebug() << "pass_chunk";
    zfile_t *file = zfile_new(ZSSettings::getInstance()->getZeroSyncDirectory().toLatin1().data(), path);
    zfile_output(file);
    zfile_write(file, zchunk_new(chunk, CHUNK_SIZE), offset);
    zfile_close(file);
    zfile_destroy(&file);
}

uint64_t ZSConnector::get_current_state()
{
    qDebug() << "current_state";
    return ZSDatabase::getInstance()->getLatestState();
}

void ZSConnector::slotSynchronizeUpdate()
{
    qDebug() << "Agent: slotSynchronizeUpdate()";
    zlist_t *updateList = zlist_new();
    QSqlQuery query = ZSDatabase::getInstance()->fetchUpdateFromState(ZSDatabase::getInstance()->getLatestState() - 1);

    while (query.next()) {
        zs_fmetadata_t *fmetadata = zs_fmetadata_new();
        zs_fmetadata_set_path(fmetadata, "%s", query.value(1).toString().toLatin1().data());
        zs_fmetadata_set_timestamp(fmetadata, query.value(3).toULongLong());
        if (query.value(2).toString().compare("UPD") == 0) {
            zs_fmetadata_set_operation(fmetadata, ZS_FILE_OP_UPD);
            zs_fmetadata_set_size(fmetadata, query.value(4).toULongLong());
            zs_fmetadata_set_checksum(fmetadata, query.value(6).toULongLong());
        }
        else
        if (query.value(2).toString().compare("REN") == 0) {
            zs_fmetadata_set_operation(fmetadata, ZS_FILE_OP_REN);
            zs_fmetadata_set_renamed_path(fmetadata, "%s", query.value(5).toString().toLatin1().data());
        }
        else
        if (query.value(2).toString().compare("DEL") == 0) {
            zs_fmetadata_set_operation(fmetadata, ZS_FILE_OP_DEL);
        }
        zlist_append(updateList, fmetadata);
    }

    if (zlist_size (updateList) > 0) {
        zsync_agent_send_update(ZSConnector::agent, ZSDatabase::getInstance()->getLatestState(), updateList);
    }
}

