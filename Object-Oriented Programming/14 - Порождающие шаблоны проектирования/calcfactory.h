#ifndef CALCFACTORY_H
#define CALCFACTORY_H
#include <bstractcalc.h>
class calcfactory
{
public:
//explicit calcfactory(QObject *parent = nullptr);
virtual bstractCalc* createCalc();
virtual ~calcfactory();
};
#endif // CALCFACTORY_H
