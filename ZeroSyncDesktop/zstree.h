/* =========================================================================
   ZSTree - Tree helper class for the ZeroWebIndex


   -------------------------------------------------------------------------
   Copyright (c) 2014 Bernhard Finger
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

#ifndef ZSTREE_H
#define ZSTREE_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <QListIterator>
#include <QtDebug>
#include <QQueue>
#include "zssettings.h"

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
