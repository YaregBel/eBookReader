#ifndef FILEPROCESSING_H
#define FILEPROCESSING_H

#include <QObject>
#include <QDebug>
#include <QApplication>
#include <iostream>
#include <QFile>

#include <QDir>

class fileProcessing : public QObject
{
    Q_OBJECT
public:
    explicit fileProcessing(QObject *parent = nullptr);
    ~fileProcessing();

    void open();
    void readFb2(QFile *pointerToFile);

signals:

};

#endif // FILEPROCESSING_H
