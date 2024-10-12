#ifndef SPECCALC_H
#define SPECCALC_H
#include <QObject>
#include <estate.h>
class speccalc : public QObject
{
Q_OBJECT
explicit speccalc(QObject *parent = nullptr);
static int getCost(Estate *value);
public:
signals:
};
#endif // SPECCALC
H
