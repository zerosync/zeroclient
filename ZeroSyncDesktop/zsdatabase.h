#ifndef ZSDATABASE_H
#define ZSDATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QStandardPaths>
#include <QFile>
#include <QSqlQuery>
#include <QTextStream>
#include <QtDebug>

class ZSDatabase : public QObject
{
    Q_OBJECT

public:
    explicit ZSDatabase(QObject *parent = 0);
    void insertNewFile(QString, qint64, QString, qint64);
    void setFileMetaData(QString, qint64, QString, qint64);
    void setFileChanged(QString, int);
    void setFileUpdated(QString, int);
    void setFileRenamed(QString, int);
    void setFileDeleted(QString, int);
    bool existsFileEntry(QString);
    bool isFileDeleted(QString);
    QSqlQuery* fetchAllChangedEntries();
    void insertNewIndexEntry(int, QString, QString, qint64, qint64, QString, QString);
    int getLatestState();
    void resetFileMetaData();

private:
    QSqlDatabase database;

    QString getDataBasePath();
    void createTables();
    bool tablesCreated();

signals:

public slots:

};

#endif // ZSDATABASE_H
