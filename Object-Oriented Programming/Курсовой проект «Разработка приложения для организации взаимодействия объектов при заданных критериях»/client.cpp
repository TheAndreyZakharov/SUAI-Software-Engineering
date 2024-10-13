#include "client.h"
client::client(QObject *parent)
    : QObject{parent}
{
}
client::client(int inputPassport, int inputPhoneNumber,QString inputFIO, QString inputEMail,QObject *parent)//конструктор
    :QObject{parent}
{
    Passport=inputPassport;
    PhoneNumber=inputPhoneNumber;
    FIO=inputFIO;
    EMail=inputEMail;
}
int client::getPassport(){//паспорт
    return Passport;
}
QString client::getFIO(){//фио
    return FIO;
}
QString client::getEMail(){//покупатель почта
    return EMail;
}
int client::getPhoneNumber(){//телефон
    return PhoneNumber;
}
clients::clients(QObject *parent)
    : QObject{parent}
{
}
clients::~clients()
{
    array.clear();//удаление о очистка array
    qDeleteAll(array);
}
bool clients::hasClients(){
    return !array.empty();//в коллекции есть элементы
}
void clients::add(client *value){
    array.append(value);//добавление элемента в коллекцию
}
