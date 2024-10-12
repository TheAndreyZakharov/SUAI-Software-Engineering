#ifndef PLANEFACTORY_H
#define PLANEFACTORY_H
#include "calcfactory.h"
#include <planecalc.h>
class planeFactory: public calcfactory
{
CALCFACTORY_H
public:
//explicit planeFactory(QObject *parent = nullptr);
bstractCalc* createCalc();
};
#endif // PLANEFACTORY_H
