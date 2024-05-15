#ifndef FILEPROCESSING_H
#define FILEPROCESSING_H

#include <QObject>
#include <QDebug>
#include <QApplication>
#include <iostream>
#include <QFile>

#include <QDir>

class FileProcessing : public QObject
{
    Q_OBJECT
public:
    explicit FileProcessing(QObject *parent = nullptr);
    ~FileProcessing();

    Q_INVOKABLE void open();
    QString readFb2(QFile *pointerToFile);
    bool fileExists(QString path);

signals:

public slots:


};

#endif // FILEPROCESSING_H
