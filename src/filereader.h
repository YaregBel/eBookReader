#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QDebug>
#include <QApplication>
#include <iostream>
#include <QFile>

#include <QDir>

class FileReader: public QObject
{
    Q_OBJECT
public:
    explicit FileReader(QObject *parent = nullptr);
    ~FileReader();

    //Q_INVOKABLE void open();
    QString readFb2(QFile *pointerToFile);
    bool fileExists(QString path);

private:

signals:
    void opened(QString book);

public slots:
    void open();

};
#endif // FILEREADER_H
