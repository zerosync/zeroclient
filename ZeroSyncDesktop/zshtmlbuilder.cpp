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

    qDebug() << tmp;

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
    result += "<div class=\"nav\">\n<p><ol class=\"breadcrumb\">\n<li><a href=\"#\">Index</a></li><li class=\"active\">Directory</li></ol></p></div>\n";
    result += "<div class=\"panel panel-default\"><h3>Synchronized files</h3>\n<div class=\"panel heading\"></div>\n";
    result += "<table class=\"table table-striped\">\n";

    int i = 0;
    int z = 0;
    while(query->next())
    {
        QString data = query->value(0).toString();

        if (data.endsWith('/')) {
            result.append("<tr id=\"folder");
            result.append(QString::number(z));
            result.append("\" class=\"folder\"><td><a href=\"#\">");
            result.append(data);
            result.append("</a>");
        }

        result.append("<tr id=\"entry");
        result.append(QString::number(i));
        result.append("\"><td width=\"80%\"><a href=\"TestFolder/");
        result.append(data);
        result.append("\">");
        result.append(data);
        result.append("</a></td>");
        result.append("<td><button type=\"button\" class=\"btn btn-default btn-sm\"><span class=\"glyphicon glyphicon-cloud-download\"></span> Download</button> ");
        result.append("<button type=\"button\" class=\"btn btn-default btn-sm\"><span class=\"glyphicon glyphicon-floppy-remove\"></span> Delete</button></td>\n");
        result.append("</tr>\n");

        i++;
    }
    result += "</table>\n";

    result += "<script src=\"https://code.jquery.com/jquery.js\"></script>\n";
    result += "<script src=\"dist/js/bootstrap.min.js\"></script>\n";
    result += "</body>\n</html>";

    return result;
}
