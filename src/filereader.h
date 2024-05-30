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
    bool readFb2(QFile *pointerToFile);
    bool fileExists(QString path);

    //QStringList listFiles(std::string pathToFiles);

private:

signals:
    void opened(QString book);
    void listGenerated(QStringList listOfFiles);


public slots:
    void open();
    QStringList listFiles(QString pathToFiles);


};
#endif // FILEREADER_H
