#ifndef CALCULATIONFACADE_H
#define CALCULATIONFACADE_H
#include <QObject>
#include <car.h>
#include "calcfactory.h"
class CalculationFacade : public QObject//базовым классом является класс QOBJECT
{
Q_OBJECT
public:
explicit CalculationFacade(QObject *parent = nullptr);//коструктор
static int getCost(car *value);//функция получения стоимости
signals:
};
#endif // CALCULATIONFACADE_H
