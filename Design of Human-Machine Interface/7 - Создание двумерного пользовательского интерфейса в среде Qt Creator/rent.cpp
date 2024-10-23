#include "rent.h"
rent::rent(int inputPassport, int inputCarNumber,QString inputIssue,QObject *parent)//конструктор
    :QObject{parent}
{
    Passport=inputPassport;
    CarNumber=inputCarNumber;
    Issue=inputIssue;
    Refund = " ";
}
int rent::getPassport(){//паспорт
    return Passport;
}
QString rent::getIssue(){//выдача
    return Issue;
}
QString rent::getRefund(){//возвр
    return Refund;
}
int rent::getCarNumber(){//возраст
    return CarNumber;
}
void rent::setRefund(QString inputRefund){
    Refund=inputRefund;
}
rented::rented(QObject *parent)
    : QObject{parent}
{
}
rented::~rented()
{
    array.clear();//удаление о очистка array
    qDeleteAll(array);
}
bool rented::hasrented(){
    return !array.empty();//в коллекции есть элементы
}
void rented::add(rent *value){
    array.append(value);//добавление элемента в коллекцию
}

