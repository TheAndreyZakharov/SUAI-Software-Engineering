#ifndef SPECFACTORY_H
#define SPECFACTORY_H
#include "calcfactory.h"
#include <speccalc.h>
class specFactory: public calcfactory
{
CALCFACTORY_H
public:
//explicit specFactory(QObject *parent = nullptr);
bstractCalc* createCalc();
};
#endif // SPECFACTORY_H
