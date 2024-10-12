#include "calculationfacade.h"
CalculationFacade::CalculationFacade(QObject *parent) : QObject(parent)
int CalculationFacade::getCost(Estate *value)
}
{
}
{
int cost;
insuranceFactory* insurance_factory = new insuranceFactory;
luxuriousFactory* luxurious_factory = new luxuriousFactory;
planeFactory* plane_factory = new planeFactory;
specFactory* spec_factory = new specFactory;
switch (value->getType())
{
case Estate::EstateType::ECONOM:
{
cost = insurance_factory->createCalc()->getCost(value);
break;
case Estate::EstateType::LUXURIOUS:
}
{
cost = luxurious_factory->createCalc()->getCost(value);
break;
case Estate::EstateType::SPEC:
}
{
cost = spec_factory->createCalc()->getCost(value);
break;
case Estate::EstateType::PLANE:
}
{
cost = plane_factory->createCalc()->getCost(value);
break;
}
default:
{
cost = -1;
break;
}
}
return cost;
}
