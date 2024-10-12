#ifndef INSURANCEFACTORY_H
#define INSURANCEFACTORY_H
#include "calcfactory.h"
#include <insurancecalc.h>
class insuranceFactory: public calcfactory
{
public:
//explicit insuranceFactory(QObject *parent = nullptr);
bstractCalc* createCalc();
};
#endif // INSURANCEFACTORY_H
