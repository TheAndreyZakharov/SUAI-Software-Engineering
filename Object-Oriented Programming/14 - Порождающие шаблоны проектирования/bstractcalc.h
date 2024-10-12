#ifndef BSTRACTCALC_H
#define BSTRACTCALC_H
#include <QObject>
#include <estate.h>
class bstractCalc : public QObject
{
Q_OBJECT
public:
explicit bstractCalc(QObject *parent = nullptr);
virtual ~bstractCalc() {};
virtual int getCost(Estate *value) = 0;
signals:
};
#endif // BSTRACTCALC_H
