#include "fileprocessing.h"

#include <QObject>
#include <QDebug>
#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>

#include <QtCore>

fileProcessing::fileProcessing(QObject *parent) : QObject(parent)
{

}

fileProcessing::~fileProcessing(){}

void fileProcessing::open(){
    //QString name = QFileDialog::getOpenFileName(this, "открыть", QDir::currentPath(), "" );
    //QString name = "/home/defaultuser/Documents/123.fb2"; -- the following code causing an error.

    //В дальнейшем заменить на динамический выбор книги
    QString name = "/Documents/123.fb2";
    if(name.isEmpty())
        return;

    if(fileExists(name)){

        QFile f(name);
        //ui->textBrowser->clear();

        if(name.endsWith(".fb2"))
        {
            readFb2(&f);
        }

    }
}

void fileProcessing::readFb2(QFile *pointerToFile){

    if (!pointerToFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // В дальнейнем заменить на вспылывающее предупреждение
        qDebug() << "файл не открыт";
        return;
    }
    else{

        QXmlStreamReader sr(pointerToFile);

        QString book;
        QString imgId;
        QString imgType;

        // In this variable we will store a list of open tags to control the structure of the book.
        QStringList thisToken;

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
                    if(sr.name() == "binary") // хранилище рисунков
                    {
                        imgId = sr.attributes().at(0).value().toString();
                        imgType = sr.attributes().at(1).value().toString();
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
    }
}

bool fileProcessing::fileExists(QString path) {
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}
