#ifndef INSURANCECALC_H
#define INSURANCECALC_H
#include <estate.h>
#include <bstractcalc.h>
class insurancecalc : public bstractCalc
{
public:
//explicit insurancecalc(QObject *parent = nullptr);
int getCost(Estate *value);
signals:
};
#endif // INSURANCECALC_H
