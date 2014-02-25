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

#include "zstree.h"

ZSTree::ZSTree(QObject *parent, ZSTree *zsancestor) :
    QObject(parent)
{
    ancestor = zsancestor;
}

/**
 * @brief ZSTree::hasChild checks if the given child, has a child.
 * @param child the given child, to check
 * @return a child, if one exists
 */
ZSTree* ZSTree::hasChild(QString child)
{
    QListIterator<ZSTree*> i(this->nodes);
    while(i.hasNext()){
        ZSTree *childNode = i.next();
        if (childNode->path.compare(child) == 0) {
            return childNode;
        }
    }
    return NULL;
}

/**
 * @brief ZSTree::addChild appends a child to a ZSTree *object
 * @param child the child to add
 * @return the new Part-Tree
 */
ZSTree* ZSTree::addChild(QString child)
{
    ZSTree *newChild = hasChild(child);
    if (newChild == NULL) {
        newChild = new ZSTree(this);
        newChild->ancestor = this;
        newChild->path = child;
        this->nodes.append(newChild);
    }
    return newChild;
}

/**
 * @brief ZSTree::append the path to Trees
 * @param path the path to append
 */
void ZSTree::append(QString path)
{
    if (path.isNull()) {
       // qDebug() << "You are a bad guy, if you want to add nothing to a Tree.";
        return;
    }

    QStringList pathList = path.split("/");
    if (pathList.length() == 1) {
        this->addChild(pathList.first());
        return;
    } else {
        ZSTree *tmp = this->addChild(pathList.takeFirst());
        return tmp->append(pathList.join("/"));

    }
}

/**
 * @brief ZSTree::getFullPath gives the fullPath of the *node in the whole tree. This is neccessairy for the web presentation.
 * @param node
 * @return the String representation of the path to the node
 */
QString ZSTree::getFullPath(ZSTree *node)
{
    if (node == NULL) {
        return ".";
    } else if (node->path.compare("") == 0) {
        return getFullPath(node->ancestor);
    } else {
        return getFullPath(node->ancestor) + "/" + node->path;
    }
}

/**
 * @brief ZSTree::toHtmlString forms the htmlString ,which is inserted in the file used in the htmlbuilder class.
 * @return the presentation of the watched filesystem as an htmlString
 */
QString ZSTree::toHtmlString()
{
    QString res;
    QQueue<ZSTree*> folderQueue;
    QQueue<ZSTree*> fileQueue;
    QString zsPathForHTML = ZSSettings::getInstance()->getZeroSyncDirectory();

    folderQueue.enqueue(this);
    while (!folderQueue.isEmpty()) {
        ZSTree *folderNode = folderQueue.dequeue();

        QListIterator<ZSTree*> i(folderNode->nodes);
        while(i.hasNext()) {
            ZSTree *childNode = i.next();

            if (childNode->nodes.isEmpty()) {
                fileQueue.enqueue(childNode);
            } else {
                folderQueue.enqueue(childNode);
            }
        }

        if (folderNode->path.compare("") != 0 && folderNode->nodes.size() > 0) {
            QString parentPathF = getFullPath(folderNode->ancestor);
            res += "<tr class=\"folder\" data-parent=\"";
            res += parentPathF + "\">";
            res += "<td width=\"80%\"><span class=\"glyphicon glyphicon-folder-open\"></span><a href=\"javascript:viewFolderFiles('";
            res += parentPathF + "/" + folderNode->path;
            res += "')\"><b>";
            res += folderNode->path;
            res += "</b></a></td><td></td></tr>";
        }
    }

    int i = 0;
    while (!fileQueue.isEmpty()) {
        ZSTree *fileNode = fileQueue.dequeue();

        QString parentPath = getFullPath(fileNode->ancestor);
        res += "<tr data-parent=\"";
        res += parentPath;
        res += "\"><td width=\"80%\"><span class=\"glyphicon glyphicon-file\"></span><a id=\""+QString::number(i)+"\"href=\"";
        res += zsPathForHTML+"/" + parentPath + "/" + fileNode->path;
        res += "\">";
        res += fileNode->path;
        res += "</a></td>";
        res += "<td><button type=\"button\" class=\"btn btn-default btn-sm\" onclick=\"downloadFile('"+zsPathForHTML+"/"+parentPath+"/"+ fileNode->path+"')\">";
        res += "<span class=\"glyphicon glyphicon-cloud-download\"></span> Download</button> ";
        res += "<button type=\"button\" class=\"btn btn-default btn-sm\" onclick=\"deleteFile('"+zsPathForHTML+"/"+parentPath+"/"+ fileNode->path+"')\"><span class=\"glyphicon glyphicon-floppy-remove\"></span> Delete</button></td>\n";
        res += "</tr>\n";
        i++;
    }
    return res;
}
