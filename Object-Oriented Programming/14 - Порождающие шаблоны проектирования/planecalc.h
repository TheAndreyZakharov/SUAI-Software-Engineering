#ifndef PLANECALC_H
#define PLANECALC_H
#include <estate.h>
#include <bstractcalc.h>
class planecalc : public bstractCalc
{
public:
//explicit planecalc(QObject *parent = nullptr);
int getCost(Estate *value);
signals:
};
#endif // PLANECALC_H
