#include "class1.h"
#include "QDebug"
#include "QApplication"

#include <QObject>
#include <QDebug>
#include <QApplication>

Class1::Class1(QObject *parent) : QObject{parent}{

}

Class1::~Class1(){};

void Class1::printFile(){
    QFile file("Documents/Data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        emit getString(QString("File is not exist."));

    QTextStream in(&file);
    QString retLine = "Содержимое файла: ";
    while (!in.atEnd()) {
        QString line = in.readLine();
        retLine += line + "\n";
    }
    emit getString(retLine);
}
