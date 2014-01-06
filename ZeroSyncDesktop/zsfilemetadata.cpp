/* =========================================================================
   ZSFileMetaData - Class to represent file metadata for the ZeroSync client


   -------------------------------------------------------------------------
   Copyright (c) 2013 Tommy Bluhm
   Copyright other contributors as noted in the AUTHORS file.

   This file is part of ZeroSync, see http://zerosync.org.

   This is free software; you can redistribute it and/or modify it under
   the terms of the GNU Lesser General Public License as published by the
   Free Software Foundation; either version 3 of the License, or (at your
   option) any later version.
   This software is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTA-
   BILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General
   Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program. If not, see http://www.gnu.org/licenses/.
   =========================================================================
*/


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
