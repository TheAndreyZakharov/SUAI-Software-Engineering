#ifndef LUXURIOUSCALC_H
#define LUXURIOUSCALC_H
#include <QObject>
#include <estate.h>
class luxuriouscalc : public QObject
{
Q_OBJECT
public:
explicit luxuriouscalc(QObject *parent = nullptr);
static int getCost(Estate *value);
signals:
};
#endif // LUXURIOUSCALC_H
