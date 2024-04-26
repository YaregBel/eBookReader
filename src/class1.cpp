#include "class1.h"
#include "QDebug"
#include "QApplication"

#include <QObject>
#include <QDebug>
#include <QApplication>

Class1::Class1(QObject *parent) : QObject{parent}{

}

Class1::~Class1(){};

void Class1::changeValue(int a){

    if(a == 1){
        emit valueChanged("Передано значение 1, из C++");
    }
    if(a == 2){
        emit valueChanged("Передано значение 2, из C++");
    }
    else{
        emit valueChanged("Отлично, ты молодец!");
    }
}
