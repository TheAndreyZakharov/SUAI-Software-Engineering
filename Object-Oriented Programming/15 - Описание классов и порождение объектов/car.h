#ifndef CAR
H
_
#define CAR_H
#include <QObject>
class car : public QObject //базовым классом является класс QOBJECT
{
Q_OBJECT
public:
enum CarType {//комплектации
STANDARD,
COMFORT,
LUXURY,
ELECTRIC
};
explicit car(int inputAge, int inputNumber,QString Colour, CarType inputCarType,QString
inputBrand,QObject *parent = nullptr);//конструктор
int getAge();
int getNumber();
QString getColour();
CarType getType();//функции получения private данных из класса
QString getBrand();
QString getTypeString();
bool condition;
int Number;
private:
int Age;//поля для записи данных с формы
QString Colour;
CarType Type;
QString Brand;
};
#endif // CAR_H
