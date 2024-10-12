#ifndef STATES_H
#define STATES_H
#include <QObject>
#include <estate.h>
class States : public QObject
{
Q_OBJECT
public:
//для 2 задания
explicit States(QObject *parent = nullptr);
~States();
void undo();
bool hasStates();
Estate *getActualData();
void add(Estate *value);
int getSize();
signals:
void notifyObservers();
private:
QList<Estate *> array;
Estate *actualData;
};
#endif
