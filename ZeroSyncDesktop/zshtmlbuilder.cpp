#include "zshtmlbuilder.h"

ZShtmlBuilder::ZShtmlBuilder(QObject *parent, ZSDatabase *zsdatabase) :
    QObject(parent)
{
    database = zsdatabase;
    folderList = new QStringList();
}


// SLOT CALLED WHEN FILE/DIRECTORY CHANGE RECOGNIZED
void ZShtmlBuilder::slotGenerateHtml(QString path)
{
    QFile file("../ZeroWebIndex.html");

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug() << "File opening failed. \n";
        return;
    }

    QString tmp = formHtml();

    QTextStream out(&file);
    out << tmp << "\n";
}

QString ZShtmlBuilder::getFileFromSubDirectories(QString key)
{
    if (map.value(key).isEmpty()) {
       // map.clear();

        return key;
    } else {
        QStringList newList = map.value(key);
        QString newKey = newList.takeFirst();

        if (!(newList.isEmpty())) {
            folderList->append(newKey);
        }

        map.insert(newKey, newList);

        return getFileFromSubDirectories(newKey);
    }
}

/**
 * @brief ZShtmlBuilder::formHtml forms the data from the database, as an html String, to prepare to embed in a .html file.
 * @return the full String with all paths.
 */
QString ZShtmlBuilder::formHtml()
{
    QSqlQuery *query = database->fetchAllUndeletedEntries();

    // HTML Header for the .html file, where this function is used for.
    QString result = "<!DOCTYPE html>\n<html>\n<head><meta charset=\"UTF-8\" /><title>Zero WEB Index</title>\n";
    result += "<link rel=\"stylesheet\" type=\"text/css\" href=\"dist/css/bootstrap.min.css\" />\n";
    result += "<link rel=\"stylesheet\" type=\"text/css\" href=\"design/CSS/menu_template.css\" />\n";
    result += "</head>\n<body style=\"background-color: #EDEDED;\">";

    result += "\n<div class=\"row\">\n <div class=\"col-lg-2\" id=\"leftSpace\"></div> \n";
    result += "<div class=\"col-lg-8\" id=\"midSpace\">\n <div class=\"row\">\n <div class=\"col-lg-3\">";
    result += "<div class=\"logo\"><img src=\"ZS_logo.png\" id=\"logo\" /></div></div>\n";
    result += "<div class=\"col-lg-6\"><div class=\"header\"><h1>Zero Sync Web</h1></div></div>";
    result += "<div class=\"col-lg-3\">\n<div class=\"upload pull-right\">\n";
    result += "<button type=\"button\" class=\"btn btn-default btn-lg\">\n<span class=\"glyphicon glyphicon-cloud-upload\"></span> Upload \n";
    result += "</button></div></div></div>\n";
    result += "<div class=\"nav\">\n<p><ol class=\"breadcrumb\">\n<li><a href=\"javascript:showRoot()\">Index</a></ol></p></div>\n";
    result += "<div aclass=\"panel panel-default\"><h3>Synchronized files</h3>\n<div class=\"panel heading\"></div>\n";
    result += "<table class=\"table table-hover\">\n";

    QStringList list;
    QMap<QString,QString> files;

    while(query->next())
    {
        QString data = query->value(0).toString();

        if (data.contains('/')) {
            list = data.split("/");

            QString folder = list.takeFirst();
            folderList->append(folder);
            map.insert(folder, list);

            QString trueFile = getFileFromSubDirectories(folder);

            QStringList listForParentDirectory = map.keys();

           // listForParentDirectory.removeLast();

            qDebug() << listForParentDirectory;

            files.insertMulti(trueFile, listForParentDirectory.last());
        }else {
            files.insert(data, "root");
        }
    }
    folderList->removeDuplicates();
    folderList->sort();

    qDebug() << files;
    result.append("<tr id=\"goBack\" style=\"display: none;\"><td><a href=\"javascript:showRoot()\"> &lt;- Go back </a></td><td></td></tr> ");

    for (int u=0; u<folderList->length(); u++)
    {
        result.append("<tr id=\"folder");
        result.append(QString::number(u));
        result.append("\" class=\"folder\"><td width=\"80%\"><a href=\"javascript:viewFolderFiles('");
        result.append(folderList->at(u));
        result.append("')\"><b>");
        result.append(folderList->at(u));
        result.append("</b></a></td><td></td></tr>");
    }

    QMapIterator<QString, QString>i(files);
    while (i.hasNext()) {
        i.next();
        if (i.value() == "root"){
            result.append("<tr class=\"fromRoot\" parent-folder=\"root\">");
            result.append("<td width=\"80%\"><a href=\"TestFolder/");
            result.append(i.key());
            result.append("\">");
            result.append(i.key());
            result.append("</a></td>");
            result.append("<td><button type=\"button\" class=\"btn btn-default btn-sm\"><span class=\"glyphicon glyphicon-cloud-download\"></span> Download</button> ");
            result.append("<button type=\"button\" class=\"btn btn-default btn-sm\"><span class=\"glyphicon glyphicon-floppy-remove\"></span> Delete</button></td>\n");
            result.append("</tr>\n");
        }else {
            result.append("<tr class=\"notFromRoot\" parent-folder=\"");
            result.append(i.value());
            result.append("\">");
            result.append("<td width=\"80%\">");
            result.append(i.key());
            result.append("</td>");
            result.append("<td><button type=\"button\" class=\"btn btn-default btn-sm\"><span class=\"glyphicon glyphicon-cloud-download\"></span> Download</button> ");
            result.append("<button type=\"button\" class=\"btn btn-default btn-sm\"><span class=\"glyphicon glyphicon-floppy-remove\"></span> Delete</button></td>\n");
            result.append("</tr>\n");
        }
    }

    result += "</table>\n";

    result += "<script src=\"https://code.jquery.com/jquery.js\"></script>\n";
    result += "<script src=\"dist/js/bootstrap.min.js\"></script>\n";
    result += "<script src=\"functionality/functions.js\"></script>\n";
    result += "</body>\n</html>";

    return result;
}
