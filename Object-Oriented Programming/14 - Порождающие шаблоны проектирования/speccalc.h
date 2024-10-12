#ifndef SPECCALC_H
#define SPECCALC_H
#include <estate.h>
#include <bstractcalc.h>
class speccalc : public bstractCalc
{
public:
//explicit speccalc(QObject *parent = nullptr);
int getCost(Estate *value);
signals:
};
#endif // SPECCALC_H
