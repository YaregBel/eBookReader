#ifndef CLASS1_H
#define CLASS1_H

#include <QObject>
#include <QDebug>
#include <QApplication>
#include <iostream>
#include <QFile>

#include <QDir>


class Class1: public QObject
{
    Q_OBJECT
public:

    explicit Class1(QObject *parent = nullptr);
    ~Class1();


signals:
    void getString(QString str1);

public slots:
    void printFile();


private:


};

#endif // CLASS1_H
