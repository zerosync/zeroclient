#include "zshtmlbuilder.h"

ZShtmlBuilder::ZShtmlBuilder(QObject *parent, ZSDatabase *zsdatabase) :
    QObject(parent)
{
    database = zsdatabase;
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

/**
 * @brief ZShtmlBuilder::formHtml forms the data from the database, as an html String, to prepare to embed in a .html file.
 * @return the full String with all paths.
 */
QString ZShtmlBuilder::formHtml()
{
    QSqlQuery *query = database->fetchAllUndeletedEntries();

    if (query == NULL) {
        qDebug() << "Database query is null, retrying...";
        formHtml();
    }

    ZSTree *fileTree = new ZSTree();

    // HTML Header for the .html file, where this function is used for.
    QString result = "<!DOCTYPE html>\n<html>\n<head><meta charset=\"UTF-8\" /><title>Zero WEB Index</title>\n";
    result += "<link rel=\"stylesheet\" type=\"text/css\" href=\"dist/css/bootstrap.min.css\" />\n";
    result += "<link rel=\"stylesheet\" type=\"text/css\" href=\"design/CSS/menu_template.css\" />\n";
    result += "</head>\n<body style=\"background-color: #EDEDED;\" onload=\"showRoot()\">";

    result += "\n<div class=\"row\">\n <div class=\"col-lg-2\" id=\"leftSpace\"></div> \n";
    result += "<div class=\"col-lg-8\" id=\"midSpace\">\n <div class=\"row\">\n <div class=\"col-lg-3\">";
    result += "<div class=\"logo\"><img src=\"ZS_logo.png\" id=\"logo\" /></div></div>\n";
    result += "<div class=\"col-lg-6\"><div class=\"header\"><h1>Zero Sync Web</h1></div></div>";
    result += "<div class=\"col-lg-3\">\n<div class=\"upload pull-right\">\n";
    result += "<div style=\"display:none;\"><input type=\"file\" id=\"file_input\" onchange=\"readUploadedFile();\" /></div>\n";
    result += "<button type=\"button\" class=\"btn btn-default btn-lg\" onclick=\"$('#file_input').click();\">\n<span class=\"glyphicon glyphicon-cloud-upload\"></span> Upload \n";
    result += "</button></div></div></div>\n";
    result += "<div class=\"nav\">\n<p><ol class=\"breadcrumb\">\n<li><a href=\"javascript:showRoot()\">Index</a></ol></p></div>\n";
    result += "<div class=\"panel panel-default\"><h3>Synchronized files</h3>\n<div class=\"panel heading\"></div>\n";
    result += "<table class=\"table table-hover\">\n";
    result += "<tr id=\"goBack\" style=\"display: none;\"></tr>";

    while(query->next())
    {   
        QString data = query->value(0).toString();   

        fileTree->append(data);
    }
    result += fileTree->toHtmlString();
    result += "</table>\n";

    result += "<script src=\"https://code.jquery.com/jquery.js\"></script>\n";
    result += "<script src=\"dist/js/bootstrap.min.js\"></script>\n";
    result += "<script src=\"functionality/functions.js\"></script>\n";
    result += "</body>\n</html>";

    return result;
}
