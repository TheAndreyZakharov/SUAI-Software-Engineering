#ifndef CALCULATIONFACADE_H
#define CALCULATIONFACADE_H
#include <QObject>
#include <estate.h>
#include <calcfactory.h>
#include <insurancefactory.h>
#include <planefactory.h>
#include <luxuriousfactory.h>
#include <specfactory.h>
class CalculationFacade : public QObject
{
Q_OBJECT
public:
explicit CalculationFacade(QObject *parent = nullptr);
static int getCost(Estate *value);
};
#endif // CALCULATIONFACADE_H
