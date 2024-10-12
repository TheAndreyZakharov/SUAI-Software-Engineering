#ifndef LUXURIOUSCALC_H
#define LUXURIOUSCALC_H
#include <estate.h>
#include <bstractcalc.h>
class luxuriouscalc : public bstractCalc
{
public:
//explicit luxuriouscalc(QObject *parent = nullptr);
int getCost(Estate *value);
signals:
};
#endif // LUXURIOUSCALC_H
