#ifndef CARUSE_H
#define CARUSE_H
#include <QObject>
class caruse : public QObject //базовым классом является класс QOBJECT
{
Q_OBJECT
public:
enum CarType {//комплектации
STANDARD,
COMFORT,
LUXURY,
ELECTRIC
};
explicit caruse(int inputAge, int inputNumber,QString Colour, CarType inputCarType,QString
inputBrand,QObject *parent = nullptr);//конструктор
int getAge();
int getNumber();
QString getColour();
CarType getType();//функции получения private данных из класса
QString getBrand();
QString getTypeString();
private:
int Age;//поля для записи данных с формы
int Number;
QString Colour;
CarType Type;
QString Brand;
};
#endif // CARUSE_H
