#ifndef INSURANCECALC_H
#define INSURANCECALC_H
#include <QObject>
#include <estate.h>
class insurancecalc : public QObject
{
Q_OBJECT
public:
explicit insurancecalc(QObject *parent = nullptr);
static int getCost(Estate *value);
signals:
};
#endif // INSURANCECALC_H
