#include "zsfilemetadata.h"

ZSFileMetaData::ZSFileMetaData(QObject *parent, QString path, QString pathToZeroSyncDirectory) :
    QObject(parent)
{
    updateFileMetaData(path, pathToZeroSyncDirectory);
}


void ZSFileMetaData::updateFileMetaData(QString path, QString pathToZeroSyncDirectory)
{
    QFileInfo fileInformations(path);
    filePath = fileInformations.absoluteFilePath().remove(0, pathToZeroSyncDirectory.length() + 1);
    fileLastModified = fileInformations.lastModified().toUTC().toMSecsSinceEpoch();
    hashOfFile = calculateHash(path);
    fileSize = fileInformations.size();
}


QString ZSFileMetaData::getFilePath()
{
    return filePath;
}


qint64 ZSFileMetaData::getLastModified()
{
    return fileLastModified;
}


QString ZSFileMetaData::getHash()
{
    return hashOfFile;
}


qint64 ZSFileMetaData::getFileSize()
{
    return fileSize;
}

QString ZSFileMetaData::calculateHash(QString path)
{
    QCryptographicHash cryptoHash(QCryptographicHash::Sha3_512);
    QFile file(path);
    file.open(QFile::ReadOnly);
    cryptoHash.addData(file.readAll());
    QByteArray hashValue = cryptoHash.result();
    return hashValue.toHex();
}
