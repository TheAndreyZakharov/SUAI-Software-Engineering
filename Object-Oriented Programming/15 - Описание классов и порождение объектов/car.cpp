#include "car.h"
car::car(int inputAge, int inputNumber,QString inputColour, CarType inputType,QString
inputBrand,QObject *parent)//конструктор
:QObject{parent}
{
Age=inputAge;
Number=inputNumber;
Colour=inputColour;
Type=inputType;
Brand=inputBrand;
condition=true;
}
int car::getNumber(){//номер
return Number;
}
QString car::getColour(){//цвет
return Colour;
}
car::CarType car::getType(){//комплектация
return Type;
}
QString car::getTypeString(){
switch (getType())//определяем тип комплектации
{
case car::CarType::STANDARD:{
return "Стандарт";
break;
}
case car::CarType::COMFORT:{
return "Комфорт";
break;
}
case car::CarType::LUXURY:{
return "Люкс";
break;
}
case car::CarType::ELECTRIC:{
return "Электро";
break;
}
}
}
QString car::getBrand(){//покупатель
return Brand;
}
int car::getAge(){//возраст
return Age;
}
