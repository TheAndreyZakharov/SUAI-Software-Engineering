#ifndef CALCFACTORY_H
#define CALCFACTORY_H
#include "car.h"
#include "abstractcalc.h"
class CalcFactory
{
public:
virtual AbstractCalc * fabrica()=0;
virtual ~CalcFactory(){};
};
// для каждой комплектации переопределяем функцию fabrica(), которая создает объект класса
вычисления стоимости
//все классы имеют родителя CalcFactory и называются фабричными
class StandardFactory : public CalcFactory
{
public:
AbstractCalc * fabrica(){return new StandardCalc;}
};
{
public:
class ElectricFactory: public CalcFactory
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
