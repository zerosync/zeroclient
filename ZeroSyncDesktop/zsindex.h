#ifndef ZSINDEX_H
#define ZSINDEX_H

#include <QObject>
#include <QtDebug>
#include <QSqlQuery>
#include <QSqlDatabase>
#include "zsdatabase.h"
#include "zsfilemetadata.h"

class ZSIndex : public QObject
{
    Q_OBJECT

public:
    explicit ZSIndex(QObject *parent = 0, ZSDatabase *zsdatabase = 0);
    void increaseLatestState();

private:
    ZSDatabase *database;
    int latestState;

signals:

public slots:
    void slotUpdateIndex();

};

#endif // ZSINDEX_H
