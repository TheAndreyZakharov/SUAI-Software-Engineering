#include "calculationfacade.h"
CalculationFacade::CalculationFacade(QObject *parent) : QObject(parent){
}
int CalculationFacade::getCost(Estate *value)
{
int cost;
switch (value->getType())
{
case Estate::EstateType::ECONOM:
{
cost = insurancecalc::getCost(value);
break;
case Estate::EstateType::LUXURIOUS:
}
{
cost = luxuriouscalc::getCost(value);
break;
case Estate::EstateType::SPEC:
}
{
cost = speccalc::getCost(value);
break;
case Estate::EstateType::PLANE:
}
{
cost = planecalc::getCost(value);
break;
}
default:
{
cost = -1;
break;
}
}
return cost;
