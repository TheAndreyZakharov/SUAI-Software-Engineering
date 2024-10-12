//аналогичны luxuriosfactory.cpp/planefactory.cpp/specfactory.cpp
#include "insurancefactory.h"
bstractCalc* insuranceFactory::createCalc()
{
return new insurancecalc;
}
