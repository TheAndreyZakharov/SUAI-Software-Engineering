#ifndef CALCFACTORY_H
#define CALCFACTORY_H
#include "car.h"
#include "abstractcalc.h"
// Factory Method использует механизм полиморфизма - классы всех конечных типов наследуют от одного абстрактного базового класса, предназначенного для полиморфного использования.
//CalcFactory - абстрактный класс для полиморфного использования, класс-фабрика
class CalcFactory
{
public:
    virtual AbstractCalc * fabrica()=0;
    virtual ~CalcFactory(){};
};
// для каждой комплектации переопределяем функцию fabrica(), которая создает объект класса вычисления стоимости
//все классы имеют родителя CalcFactory и называются фабричными
class StandardFactory : public CalcFactory
{
public:
    AbstractCalc * fabrica(){return new StandardCalc;}
};
class ElectricFactory: public CalcFactory
{
public:
    AbstractCalc * fabrica(){return new ElectricCalc;}
};

class ComfortFactory: public CalcFactory
{
public:
    AbstractCalc * fabrica(){return new ComfortCalc;}
};

class LuxuryFactory: public CalcFactory
{
public:
    AbstractCalc * fabrica(){return new LuxuryCalc;}
};
#endif // CALCFACTORY_H
