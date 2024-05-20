#ifndef TXTFILEREADER_H
#define TXTFILEREADER_H

#include <QObject>
#include <QDebug>
#include <QApplication>
#include <iostream>
#include <QFile>

#include <QDir>

class txtfilereader: public QObject
{
    Q_OBJECT
public:
    explicit txtfilereader(QObject *parent = nullptr);
    ~txtfilereader();

    Q_INVOKABLE void open();
    QString readFb2(QFile *pointerToFile);
    bool fileExists(QString path);

signals:

public slots:


};



#endif // TXTFILEREADER_H
