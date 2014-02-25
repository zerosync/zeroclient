/* =========================================================================
   ZSHtmlBuilder - Class that creates the ZeroWebIndex html file


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

#ifndef ZSHTMLBUILDER_H
#define ZSHTMLBUILDER_H

#include <QObject>
#include <QSqlQuery>
#include <QtDebug>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QMap>
#include <QStringList>
#include "zsdatabase.h"
#include "zstree.h"


//!  Class Description Title
/*!
  Class description
*/
class ZShtmlBuilder : public QObject
{
    Q_OBJECT

public:
    explicit ZShtmlBuilder(QObject *parent = 0);
    QString formHtml();


public slots:
        void slotGenerateHtml();

};

#endif // ZSHTMLBUILDER_H
