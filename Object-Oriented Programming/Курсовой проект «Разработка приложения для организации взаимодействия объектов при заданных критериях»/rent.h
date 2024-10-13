#ifndef RENT_H
#define RENT_H
#include <QObject>
class rent : public QObject
{
    Q_OBJECT
public:
    explicit rent(int inputPassport, int inputCarNumber,QString Issue,QObject *parent = nullptr);//конструктор
    int getPassport();
    int getCarNumber();
    QString getIssue();//функции получения private данных из класса
    QString getRefund();
    void setRefund(QString inputRefund);
    int CarNumber;
private:
    int Passport;//поля для записи данных с формы
    QString Issue;
    QString Refund;
};
class rented : public QObject//базовым классом является класс QOBJECT
{
    Q_OBJECT
public:
    explicit rented(QObject *parent = nullptr);
    ~rented();
    bool hasrented();//наличие элементов в коллекции
    void add(rent *value);//добавление элемента в коллекцию
    QList<rent *> array;//список в котором храняться элементы класса estate
};
#endif // RENT_H
