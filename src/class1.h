#ifndef CLASS1_H
#define CLASS1_H

#include <QObject>
#include <QDebug>
#include <QApplication>
#include <iostream>

#include <QDir>


class Class1: public QObject
{
    Q_OBJECT
public:

    explicit Class1(QObject *parent = nullptr);
    ~Class1();

    Q_INVOKABLE void printPath() {
        QDir dir = QDir::root();                 // "/"
        if (!dir.cd("tmp")) {                    // "/tmp"
            qWarning("Cannot find the \"/tmp\" directory");
        } else {
            QFile file(dir.filePath("ex1.txt")); // "/tmp/ex1.txt"
            if (!file.open(QIODevice::ReadWrite))
                qWarning("Cannot create the file");
        }
    };


private:


};

#endif // CLASS1_H
