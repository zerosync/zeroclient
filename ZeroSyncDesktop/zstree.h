#ifndef ZSTREE_H
#define ZSTREE_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <QListIterator>
#include <QtDebug>
#include <QQueue>

class ZSTree : public QObject
{
    Q_OBJECT

public:
    explicit ZSTree(QObject *parent = 0, ZSTree *ancestor = 0);
    ZSTree* addChild(QString child);
    ZSTree* hasChild(QString child);
    void append(QString path);
    QString getFullPath(ZSTree *node);
    QString toHtmlString();

private:
    ZSTree *ancestor;
    QString path;
    QList<ZSTree*> nodes;
};


#endif // ZSTREE_H
