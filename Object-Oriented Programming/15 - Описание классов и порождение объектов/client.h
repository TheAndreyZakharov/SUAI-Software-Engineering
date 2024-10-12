#ifndef CLIENT_H
#define CLIENT_H
#include <QObject>
class client : public QObject
{
Q_OBJECT
public:
explicit client(QObject *parent = nullptr);
explicit client(int inputPassport, int inputPhoneNumber,QString inputFIO,QString inputEMail,QObject
*parent = nullptr);//конструктор
int getPassport();
int getPhoneNumber();
QString getFIO();//функции получения private данных из класса
QString getEMail();
private:
int Passport;//поля для записи данных с формы
int PhoneNumber;
QString FIO;
QString EMail;
signals:
};
class clients : public QObject//базовым классом является класс QOBJECT
{
Q_OBJECT
public:
explicit clients(QObject *parent = nullptr);
~clients();
//void undo();//функция манипулирует над actualdata добавляя в нее значение или null
bool hasClients();//наличие элементов в коллекции
//car *getActualData();//функция возвращающая последний элемент коллекции
void add(client *value);//добавление элемента в коллекцию
QList<client *> array;//список в котором храняться элементы класса estate
//car *actualData;//последний элемент коллекции
signals:
//void notifyObservers();//сигнал наблюдателю
};
#endif // CLIENT_H
Текст программы (clients.h)
#ifndef CLIENTS_H
#define CLIENTS_H
#include <QObject>
class clientss : public QObject
{
Q_OBJECT
public:
explicit clientss(QObject *parent = nullptr);
signals:
};
#endif // CLIENTS_H
