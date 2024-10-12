#ifndef LUXURIOUSFACTORY_H
#define LUXURIOUSFACTORY_H
#include "calcfactory.h"
#include <luxuriouscalc.h>
class luxuriousFactory: public calcfactory
{
CALCFACTORY_H
public:
//explicit luxuriousFactory(QObject *parent = nullptr);
bstractCalc* createCalc();
};
#endif // LUXURIOUSFACTORY_H
