#ifndef CLASS1_H
#define CLASS1_H

#include <QObject>
#include <QDebug>
#include <QApplication>


class Class1: public QObject
{
    Q_OBJECT
public:

    explicit Class1(QObject *parent = nullptr);
    ~Class1();

    Q_INVOKABLE void printPath() {qDebug() << "App path : " << qApp->applicationDirPath();};

private:


};

#endif // CLASS1_H
