#include "fileprocessing.h"

#include <QObject>
#include <QDebug>
#include <QApplication>
#include <QFileDialog>

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

    QFile f(name);

    //ui->textBrowser->clear();

    if(name.endsWith(".fb2"))
    {
        readFb2(&f);
    }

}

void fileProcessing::readFb2(QFile *pointerToFile){

    if (!pointerToFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // В дальнейнем заменить на вспылывающее предупреждение
        qDebug() << "файл не открыт";
        return;
    }


}
