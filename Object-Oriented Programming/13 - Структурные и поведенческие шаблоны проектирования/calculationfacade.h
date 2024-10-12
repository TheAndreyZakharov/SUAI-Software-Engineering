#ifndef CALCULATIONFACADE_H
#define CALCULATIONFACADE_H
#include <QObject>
#include <estate.h>
#include <insurancecalc.h>
speccalc
getCost()
observer
update()
Form
пользователь
getActualData()
#include <luxuriouscalc.h>
#include <speccalc.h>
#include <planecalc.h>
class CalculationFacade : public QObject
{
Q_OBJECT
public:
explicit CalculationFacade(QObject *parent = nullptr);
static int getCost(Estate *value);
};
#endif // CALCULATIONFACADE_H
