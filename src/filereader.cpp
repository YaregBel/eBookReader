#include "filereader.h"

#include "QDebug"
#include "QApplication"

#include <QObject>
#include <QDebug>
#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>

#include <QtCore>
// Importing for working with directories
#include <filesystem>

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


    QString name = "Documents/123.fb2";
    qDebug()<<name;
    if(name.isEmpty())
        return;
    QFile file("Documents/123.fb2");
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

//    QStringList listOfFiles;
//    std::string path = "Documents";
//    for (const auto & entry : std::filesystem::directory_iterator(path)){
//        std::cout << entry.path() << std::endl;
//        listOfFiles.append(QString::fromStdString(entry.path()));
//    }
//    qDebug() << listOfFiles;





//    if(fileExists(name)){
//        qDebug()<<"Файл существует";
//        QFile f(name);
//        //ui->textBrowser->clear();

//        if(name.endsWith(".fb2"))
//        {
//            readFb2(&f);
//        }

//    }
}

bool FileReader::readFb2(QFile *pointerToFile){
    if (!pointerToFile->open(QIODevice::ReadOnly | QIODevice::Text))
        {
            // В дальнейнем заменить на вспылывающее предупреждение
            qDebug() << "файл не открыт";
            return false;
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

            emit opened(book);
            return true;
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
