#ifndef ZSFILEMETADATA_H
#define ZSFILEMETADATA_H

#include <QObject>
#include <QtDebug>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QFile>
#include <QByteArray>
#include <QDateTime>

class ZSFileMetaData : public QObject
{
    Q_OBJECT
public:
    explicit ZSFileMetaData(QObject *parent = 0, QString path = QString(), QString pathToZeroSyncDirectory = QString());
    QString getFilePath();
    qint64 getLastModified();
    QString getHash();
    qint64 getFileSize();

private:
    QString filePath;
    qint64 fileLastModified;
    QString hashOfFile;
    qint64 fileSize;

    void updateFileMetaData(QString, QString);
    QString calculateHash(QString);

signals:

public slots:

};

#endif // ZSFILEMETADATA_H
