#ifndef ABSTRACTCALC_H
#define ABSTRACTCALC_H
#include "car.h"
//абстрактный класс для создания объектов классов расчета
class AbstractCalc
{
public:
AbstractCalc();
virtual int getCost(car *value)=0;
virtual ~AbstractCalc(){};
};
// Класс создаваемый для расчета стоимости стандартной комплектации
//все классы имеют родителя AbstractCalc и являются объектами конечных типов
class StandardCalc : public AbstractCalc
{
public:
int getCost(car *value){
return (((value->getAge()))*50);
}
};
// Класс создаваемый для расчета стоимости для авто комфорт класса
class ComfortCalc : public AbstractCalc
{
public:
int getCost(car *value){
return (((value->getAge()))*70);
}
};
// Класс создаваемый для расчета стоимости для люкс
class LuxuryCalc : public AbstractCalc
{
public:
int getCost(car *value){
return (((value->getAge()))*90);
}
};
// Класс создаваемый для расчета стоимости для электро
class ElectricCalc : public AbstractCalc
{
public:
int getCost(car *value){
return (((value->getAge()))*80);
}
};
#endif // ABSTRACTCALC_H
