#include "filereader.h"

#include "QDebug"
#include "QApplication"

#include <QObject>
#include <QDebug>
#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>

#include <QtCore>

FileReader::FileReader(QObject *parent) : QObject(parent)
{

}

FileReader::~FileReader(){}

QString text;
QStringList content;

void FileReader::open(){
    //QString name = QFileDialog::getOpenFileName(this, "открыть", QDir::currentPath(), "" );
    //QString name = "/home/defaultuser/Documents/123.fb2"; -- the following code causing an error.
    //В дальнейшем заменить на динамический выбор книги
    QString name = "/Documents/test.txt";
    qDebug()<<name;
    if(name.isEmpty())
        return;
    QFile file("Documents/123.fb2");
    QTextStream in(&file);
    QString retLine = "Содержимое файла: ";
    while (!in.atEnd()) {
        QString line = in.readLine();
        retLine += line + "\n";
    }
    QFileInfo checkF(file);
    readFb2(&file);

    if(fileExists(name)){
        qDebug()<<"Файл существует";
        QFile f(name);
        //ui->textBrowser->clear();

        if(name.endsWith(".fb2"))
        {
            readFb2(&f);
        }

    }
}

QString FileReader::readFb2(QFile *pointerToFile){

    qDebug() << "Метод чтения сработал";
    if (!pointerToFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // В дальнейнем заменить на вспылывающее предупреждение
        qDebug() << "файл не открыт";
        return "";
    }
    else{
        qDebug() << "Файл открыт";
        QXmlStreamReader sr(pointerToFile);

        QString book;
        QString imgId;
        QString imgType;

        QString opt;
        QString special;


        // In this variable we will store a list of open tags to control the structure of the book.
        QStringList thisToken;

        int fontSize = 20;
        if( QSysInfo::productType() == "android" )
            fontSize *= 1.8;


        while( !sr.atEnd() )
            {
            switch( sr.readNext() )
                {
                // Что-то не получилось...
                case QXmlStreamReader::NoToken:
                    qDebug() << "QXmlStreamReader::NoToken";
                    break;
                // Случай открытия книги и начала ее чтения
                case QXmlStreamReader::StartDocument:
                    // Добавляем открывающиеся тэги для обработки, когда начинаем читать файл
                    book = "<!DOCTYPE HTML><html><body style=\"font-size:14px\">";
                    break;
                // Случай закрытия книги и конца ее чтения
                case QXmlStreamReader::EndDocument:
                    // Закрываем ранее добавленные теги, когда закончили считывать книгу.
                    book.append("</body></html>");
                    break;
                // Встречаем открывающийся тег.
                case QXmlStreamReader::StartElement:
                    thisToken.append( sr.name().toString() );
                    if( sr.name().toString() == "image" ) // расположение рисунков
                    {
                        if(sr.attributes().count() > 0)
                            book.append("<p align=\"center\">"+sr.attributes().at(0).value().toString()+"</p>");
                    }

                    thisToken.append( sr.name().toString() );

                    if(thisToken.contains("description")) // ОПИСАНИЕ КНИГИ
                    {
                        if( thisToken.back() != "image" ) //пропускаем всё кроме обложки
                            break; // не выводим
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
                                imgId = sr.attributes().at(0).value().toString(); // ссылка на текст
                                imgId = "";
                            }
                        }
                    }

                    opt = " align=\"justify\"";
                    if(thisToken.contains("title") )
                    {
                        opt = " align=\"center\" style=\"font-size:" +QString::number(int(fontSize * 1.5)) + "px\" ";
                        if(special == "notes")
                        {
                            opt += (" id=\"" + imgId + "\"");
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
                        imgId= "";
                        for(int i = 0; i < sr.attributes().count(); i++)
                        {
                            if(sr.attributes().at(i).name() == "type" )
                            {
                                //rType = sr.attributes().at(i).value().toString();
                            }
                            if(sr.attributes().at(i).name() == "href")
                            {
                                imgId = sr.attributes().at(i).value().toString();
                            }
                        }
                        book.append("<a href=\"" + imgId + "\"> ");
                        //qDebug() << "a" << rId;
                    }
                    if(sr.name().toString() == "poem"
                            || sr.name().toString() == "stanza"
                            || sr.name().toString() == "epigraph")
                    {
                        break;
                    }
                    if(sr.name().toString() == "text-author" ) // автор текстта
                    {
                        book.append( "<p align=\"justify\" style=\"margin-left:45px;\">" );
                        break;
                    }
                    if(sr.name().toString() == "date" ) // автор текстта
                    {
                        book.append( "<p align=\"justify\" style=\"margin-left:45px;\">" );
                        break;
                    }
                    if(sr.name() == "binary") // хранилище рисунков
                    {
                        if (sr.attributes().at(0).name() == "id"){
                            imgId = sr.attributes().at(0).value().toString();
                            imgType = sr.attributes().at(1).value().toString();
                        }
                        if (sr.attributes().at(1).name() == "id"){
                            imgId = sr.attributes().at(1).value().toString();
                            imgType = sr.attributes().at(0).value().toString();
                        }
                    }
                    break;
                // Встречаем закрывающийся тег.
                case QXmlStreamReader::EndElement:
                    if( thisToken.last() == sr.name().toString() )
                        thisToken.removeLast();
                    else
                        qDebug() << "error token";
                    break;
                // Используется для чего-то типа аннотаций, пояснений.
                case QXmlStreamReader::Characters:
                    if( sr.text().toString().contains( QRegExp("[A-Z]|[a-z]|[А-Я]|[а-я]") )) // если есть текст в блоке
                    {
                        if(thisToken.contains("description")) // ОПИСАНИЕ КНИГИ
                        {
                            break; // не выводим
                        }
                        if(thisToken.contains("div"))
                            break;
                        if(!thisToken.contains( "binary" ))
                            book.append("<p>" + sr.text().toString() + "</p>");
                    }
                    if(thisToken.contains( "binary" ) )//для рисунков
                    {
                        QString image = "<img src=\"data:"
                                + imgType +";base64,"
                                + sr.text().toString()
                                + "\"/>";
                        book.replace("#"+imgId, image);
                    }
                    break;
                }
            }

        qDebug()<<"Метод отработал";
        qDebug()<< book;
        emit opened(book);
        return book;
    }
}

bool FileReader::fileExists(QString path) {
    qDebug()<<"Условие вызвано"+path;
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        qDebug()<<"Ага";
        return true;
    } else {
        qDebug()<<check_file.exists();
        return false;
    }
}
