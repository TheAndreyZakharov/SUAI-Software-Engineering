#ifndef PLANECALC_H
#define PLANECALC_H
#include <QObject>
#include <estate.h>
class planecalc : public QObject
{
Q_OBJECT
explicit planecalc(QObject *parent = nullptr);
static int getCost(Estate *value);
public:
signals:
};
#endif // PLANECALC_H
