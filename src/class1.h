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

    Q_INVOKABLE void printPath() {
        qDebug() << "App path : " << qApp->applicationDirPath();
        qDebug() << "ldksajf;sjadfl";};
    Q_INVOKABLE QString getTextSize() {return fieldValue; }

private:
    int textSize {18};
    QString fieldValue {"Текст изменен!"};


};

#endif // CLASS1_H
