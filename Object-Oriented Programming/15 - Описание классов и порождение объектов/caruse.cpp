#include "caruse.h"
caruse::caruse(int inputAge, int inputNumber,QString inputColour, CarType inputType,QString
inputBrand,QObject *parent)//конструктор
:QObject{parent}
{
Age=inputAge;
Number=inputNumber;
Colour=inputColour;
Type=inputType;
Brand=inputBrand;
}
int caruse::getNumber(){//номер
return Number;
}
QString caruse::getColour(){//цвет
return Colour;
}
caruse::CarType caruse::getType(){//комплектация
return Type;
}
QString caruse::getTypeString(){
switch (getType())//определяем тип комплектации
{
case caruse::CarType::STANDARD:{
return "Стандарт";
break;
}
case caruse::CarType::COMFORT:{
return "Комфорт";
break;
}
case caruse::CarType::LUXURY:{
return "Люкс";
break;
}
case caruse::CarType::ELECTRIC:{
return "Электро";
break;
}
}
}
QString caruse::getBrand(){//покупатель
return Brand;
}
int caruse::getAge(){//возраст
return Age;
}
