#include "filereader.h"
#include "QDebug"
#include "QApplication"

#include <QObject>
#include <QDebug>
#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>

#include <QtCore>
#include <filesystem>
#include <QQuickView>
#include <QTextBrowser>

#include <QGuiApplication>
#include <QTextBrowser>
#include <QWidget>

FileReader::FileReader(QObject *parent) : QObject(parent)
{

}

FileReader::~FileReader(){}

void FileReader::open(){

    QStringList listOfFiles = listFiles("Documents");
    qDebug() << listOfFiles;

    QString name = listOfFiles[0];
    qDebug()<<name;
    if(name.isEmpty())
        return;

    if(fileExists(name)){

        QFile f(name);

        if(name.endsWith(".fb2"))
        {
            readFb2(&f);
        }

    }
}

QStringList FileReader::listFiles(std::string pathToFiles){

    QStringList listOfFiles;

    for (const auto & entry : std::filesystem::directory_iterator(pathToFiles)){
        std::cout << entry.path() << std::endl;
        listOfFiles.append(QString::fromStdString(entry.path()));
    }

    return listOfFiles;

}

bool FileReader::readFb2(QFile *pointerToFile){
    QFile *f = pointerToFile;
             if (!f->open(QIODevice::ReadOnly | QIODevice::Text))
             {
                 qDebug() << "файл не открыт";
                 return false;
             }
             bool ok = true;
             QString special;
             QString description;

             int fontSize = 20;
             if( QSysInfo::productType() == "android" )
                 fontSize *= 1.8;

             QXmlStreamReader sr(f);


             QString book;
             QString rId;
             QString rType;
             QString opt;

             QStringList thisToken, content;

             while( !sr.atEnd() )
             {
                 switch( sr.readNext() )
                 {
         case QXmlStreamReader::NoToken:
                     qDebug() << "QXmlStreamReader::NoToken";
                     break;
         case QXmlStreamReader::StartDocument:
                     book = "<!DOCTYPE HTML><html><body style=\"font-size:%1px; font-family:Sans, Times New Roman;\">";
                     book = book.arg(fontSize);
                     break;
         case QXmlStreamReader::EndDocument:
                     book.append("</body></html>");
                     break;
         case QXmlStreamReader::StartElement:
                     thisToken.append(sr.name().toString());

                     if(thisToken.contains("description")) // ОПИСАНИЕ КНИГИ
                     {

                         if( thisToken.back() != "image"
                                 && thisToken.back() != "first-name"
                                 && thisToken.back() != "last-name"
                                 && thisToken.back() != "book-title")
                             {
                             break;
                             }// не выводим
                     }

                     if(sr.name().toString() == "title")
                     {
                         content.append(""); // добавляем пункт содержания
                         break;
                     }

                     if( sr.name().toString() == "body" )
                         if( !sr.attributes().isEmpty()
                             && sr.attributes().first().value().toString() == "notes")
                             special = "notes";  // режим примечаний

                     if(special == "notes")
                     {
                         if( sr.name().toString() == "section" )
                         {
                             if( sr.attributes().count() > 0 )
                             {
                                 rId = sr.attributes().at(0).value().toString(); // ссылка на текст
                                 rType = "";
                             }
                         }
                     }

                     opt = " align=\"justify\"";
                     if(thisToken.contains("title") &&  sr.name().toString()=="p")
                     {
                         book.append("<h1>");

                         if(special == "notes")
                         {
                             opt += (" id=\"" + rId + "\"");

                         }
                     }
                     if(thisToken.contains("subtitle") )
                     {
                         opt = " align=\"center\" style=\"font-size:" +QString::number(int(fontSize * 1.2)) + "px\" ";
                     }
                     if(thisToken.contains("annotation") )
                     {
                         opt = " align=\"left\" ";
                     }

                     if(sr.name().toString() == "p"
                             || sr.name().toString() == "subtitle")
                     {
                         book.append("<p"+opt +" >");
                         break;
                     }
                     if (sr.name().toString()=="title")
                        {
                         book.append("<h1>");


                     }

                     if( sr.name().toString() == "table" )
                     {
                         QString text;
                         for(int i = 0; i < sr.attributes().count(); i++)
                         {
                             if(sr.attributes().at(i).name() == "id")
                                 qDebug() << sr.attributes().at(i).value().toString();
                             if(sr.attributes().at(i).name() == "style")
                                 text.append( "style=\"" +sr.attributes().at(i).value().toString()+ ";\"" );
                         }
                         book.append("<table border=1 align=\"center\" style=\"border:solid;\" " + text + ">");
                         break;
                     }
                     if( sr.name().toString() == "tr" )
                     {
                         QString text;
                         if(!thisToken.contains("table"))
                             qDebug() << "ошибка в таблице";
                         for(int i = 0; i < sr.attributes().count(); i++)
                         {
                             if(sr.attributes().at(i).name() == "aling")
                                 text.append( "aling=\"" +sr.attributes().at(i).value().toString()+ "\"" );
                             else
                                 qDebug() << "<tr>" << sr.attributes().at(i).name() << sr.attributes().at(i).value().toString();
                         }
                         book.append("<tr " + text + ">");
                         break;
                     }            //
                     if( sr.name().toString() == "td"
                          || sr.name().toString() == "th" )
                     {
                         if(!thisToken.contains("table"))
                             qDebug() << "ошибка в таблице";
                         QString text;
                         for(int i = 0; i < sr.attributes().count(); i++)
                         {
                             if(sr.attributes().at(i).name() == "aling")
                                 text.append( "aling=\"" +sr.attributes().at(i).value().toString()+ "\" " );
                             else if(sr.attributes().at(i).name() == "valing")
                                 text.append( "valing=\"" +sr.attributes().at(i).value().toString()+ "\" " );
                             else if(sr.attributes().at(i).name() == "colspan")
                                 text.append( "colspan=" +sr.attributes().at(i).value().toString()+ " " );
                             else if(sr.attributes().at(i).name() == "rowspan")
                                 text.append( "rowspan=" +sr.attributes().at(i).value().toString()+ " " );
                             else
                                 qDebug() << "<td th>" << sr.attributes().at(i).name() << sr.attributes().at(i).value().toString();
                         }
                         book.append( "<"+sr.name().toString()+ " " + text +">" );
                         break;
                     }
                     if( sr.name().toString() == "empty-line" )
                     {
                         book.append("<br/>");
                         break;
                     }
                     if(sr.name().toString() == "strong"
                             || sr.name().toString() == "sup"
                             || sr.name().toString() == "sub"
                             || sr.name().toString() == "code"
                             || sr.name().toString() == "cite")
                     {
                         book.append( "<" + sr.name().toString() + ">");
                         break;
                     }
                     if(sr.name().toString() == "emphasis")
                     {
                         book.append( "<i>" );
                         break;
                     }
                     if( sr.name().toString() == "v" )
                     {
                         book.append("<p align=\"left\" style=\"margin-left:25px;\">");
                         break;
                     }
                     if(sr.name().toString() == "strikethrough")
                     {
                         book.append( "<strike>" );
                         break;
                     }

                     if( sr.name().toString() == "a" ) // метка примечания
                     {
                         rId = "";
                         for(int i = 0; i < sr.attributes().count(); i++)
                         {
                             if(sr.attributes().at(i).name() == "type" )
                             {
                                 //rType = sr.attributes().at(i).value().toString();
                             }
                             if(sr.attributes().at(i).name() == "href")
                             {
                                 rId = sr.attributes().at(i).value().toString();
                             }
                         }
                         book.append("<a href=\"" + rId + "\"> ");
                         //qDebug() << "a" << rId;
                     }

                     if(sr.name().toString() == "poem"
                             || sr.name().toString() == "stanza"
                             || sr.name().toString() == "epigraph")
                     {
                         break;
                     }

                     if(sr.name().toString() == "author" ) // автор текстта
                     {

                         book.append( "<p align=\"justify\" style=\"margin-left:45px;\">" );
                         break;
                     }
                     if(sr.name().toString() == "date" )
                     {
                         book.append( "<p align=\"justify\" style=\"margin-left:45px;\">" );
                         break;
                     }

                     if( sr.name().toString() == "image" ) // расположение рисунков
                     {
                         if(sr.attributes().count() > 0)
                             book.append("<p align=\"center\">"+sr.attributes().at(0).value().toString() + "#" + "</p>");
                     }
                     if(sr.name() == "binary") // хранилище рисунков
                     {
                         if(sr.attributes().at(0).name() == "id")
                         {
                             rId = sr.attributes().at(0).value().toString();
                             rType = sr.attributes().at(1).value().toString();
                         }
                         if(sr.attributes().at(1).name() == "id")
                         {
                             rId = sr.attributes().at(1).value().toString();
                             rType = sr.attributes().at(0).value().toString();
                         }
                     }
                     break;
         case QXmlStreamReader::EndElement:
                     if( thisToken.last() == sr.name().toString() )
                     {
                         thisToken.removeLast();
                     }
                     else
                         qDebug() << "error token";

                     if( sr.name().toString() == "p"
                             || sr.name().toString() == "subtitle"
                             || sr.name().toString() == "v"
                             || sr.name().toString() == "date"
                             || sr.name().toString() == "author")
                     {
                         book.append("</p>");
                         break;
                     }
                     if( sr.name().toString() == "title")
                     {
                         book.append("</h1>");
                         qDebug()<<"-------------------------------------Закрыл заголовок!";
                         break;
                     }

                     if(sr.name().toString() == "td"
                             || sr.name().toString() == "th"
                             || sr.name().toString() == "tr"
                             || sr.name().toString() == "table"
                             || sr.name().toString() == "sup"
                             || sr.name().toString() == "sub"
                             || sr.name().toString() == "strong"
                             || sr.name().toString() == "code"
                             || sr.name().toString() == "cite")
                     {
                         book.append( "</"+sr.name().toString()+">" );
                         break;
                     }

                     if( sr.name().toString() == "a" )
                     {
                         rId.remove("#");
                         book.append( "</a><span id=\"" + rId + "___" + "\"></span>" );
                         qDebug() << "id" << rId + "___";
                         break;
                     }

                     if(sr.name().toString() == "emphasis")
                     {
                         book.append( "</i>" );
                         break;
                     }
                     if(sr.name().toString() == "strikethrough")
                     {
                         book.append( "</strike>" );
                         break;
                     }

                     if(sr.name().toString() == "stanza") // конец строфы
                     {
                         //book->append("<br/>");
                         break;
                     }
                     if(sr.name().toString() == "epigraph"
                             || sr.name().toString() == "poem")
                     {
                         break;
                     }

                     if(special == "notes") // режим извлечения примечаний
                     {
                         if( sr.name().toString() == "body" )
                         {
                             special = "";
                         }
                         if( sr.name().toString() == "section" )
                         {
                             book.insert(book.lastIndexOf("<"), "<a href=\"#" + rId + "___" + "\"> назад</a>");
                         }
                     }
                     break;
          case QXmlStreamReader::Characters:
                     if( sr.text().toString() == "" )
                     {
                         //qDebug() << "isEmpty";
                         break;
                     }
                     if( sr.text().toString() == "\n" )
                     {
                         //qDebug() << "isEmpty";
                         break;
                     }

                     if(thisToken.contains("description")) // ОПИСАНИЕ КНИГИ
                     {

                         description.append(sr.text().toString() + " ");
                         break;
                     }

                     if(thisToken.contains( "binary" ) ) // для рисунков
                     {
                         QString image = "<img src=\"data:"
                                 + rType +";base64,"
                                 + sr.text().toString()
                                 + "\"/>";
                         book.replace("#"+rId +"#", image);
                         rId = "";
                         rType = "";

                         break;
                     }
                     if(thisToken.contains("div"))
                     {
                         qDebug() << "div" << sr.text().toString();
                         break;
                     }
                     if(thisToken.back() == "FictionBook")
                     {
                         qDebug() << "FictionBook" << sr.text().toString();
                         break;
                     }

                     if( thisToken.contains("title") ) // формируем содержание
                     {
                         content.back() += " " + sr.text().toString();
                         qDebug() << "title" << sr.text().toString();
                     }

                     if(special == "notes" && !thisToken.contains("title") )  // добавление текста примечания
                     {
                         rType += " ";
                         rType += sr.text().toString();
                         //break;
                     }

                     if(thisToken.back() == "p"
                             || thisToken.back() == "subtitle"
                             || thisToken.back() == "v"
                             || thisToken.back() == "emphasis"
                             || thisToken.back() == "strong"
                             || thisToken.back() == "strikethrough"
                             || thisToken.back() == "sup"
                             || thisToken.back() == "sub"
                             || thisToken.back() == "td"
                             || thisToken.back() == "th"
                             || thisToken.back() == "code"
                             || thisToken.back() == "cite"
                             || thisToken.back() == "author"  // ??
                             || thisToken.back() == "date"
                             )
                     {
                         book.append( sr.text().toString() );
                         break;
                     }

                     if(thisToken.back() == "section")
                     {
                         qDebug() << "section" << sr.text().toString();
                         break;
                     }
                     if(thisToken.back() == "body")
                     {
                         qDebug() << "body" << sr.text().toString();
                         break;
                     }
                     if(thisToken.back() == "table"
                             || thisToken.back() == "tr"
                             || thisToken.back() == "title"
                             || thisToken.back() == "poem"
                             || thisToken.back() == "stanza")
                     {
                         break;
                     }
                     if(thisToken.back() == "annotation")
                     {
                         qDebug() << "annotation" << sr.text().toString();
                         break;
                     }

                     if(thisToken.back() == "a")
                     {
                         book.append( sr.text().toString() );
                         break;
                     }
                     //все прочие тэги
                     if( !sr.text().toString().isEmpty() )
                     {
                         qDebug() << thisToken.back() <<  "исключение" ;
                         book.append("<span> " + sr.text().toString() + "</span>");
                     }
                     break;
                 }
             }
             f->close();
             emit opened(book);
             return ok;
}

bool FileReader::fileExists(QString path) {
    qDebug()<<"Условие вызвано"+path;
    QFileInfo check_file(path);
    if (check_file.exists() && check_file.isFile()) {
        qDebug()<<"Ага";
        return true;
    } else {
        qDebug()<<check_file.exists();
        return false;
    }
}
