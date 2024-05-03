#include "fileprocessing.h"

#include <QObject>
#include <QDebug>
#include <QApplication>
#include <QFileDialog>

fileProcessing::fileProcessing(QObject *parent) : QObject(parent)
{

}

fileProcessing::~fileProcessing(){}

void fileProcessing::open(){
    //QString name = QFileDialog::getOpenFileName(this, "открыть", QDir::currentPath(), "" );
    //QString name = "/home/defaultuser/Documents/123.fb2"; -- the following code causing an error.
    QString name = "";
        if(name.isEmpty())
            return;

        QFile f(name);

        //ui->textBrowser->clear();

        if(name.endsWith(".fb2"))
        {
            //readFb2(&f);
            readFb2(name);
        }

}

void fileProcessing::readFb2(QString filePath){

    filePath += "";
}
