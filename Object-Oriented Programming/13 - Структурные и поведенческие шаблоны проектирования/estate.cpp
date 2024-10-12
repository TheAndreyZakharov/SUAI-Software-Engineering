//для 1 задания
#include "estate.h"
#include <widget.h>
Estate::Estate(QObject *parent)
: QObject(parent)
{
age = 6;
hp = 110;
residents = 1;
months = 12;
owner = "ZA9AB01E0PCD39023";
type = Estate::ECONOM;
}
Estate::Estate(const int age, const int hp, const int residents,
const int months, const EstateType type, const QString owner)
{
this->age = age;
this->hp = hp;
this->residents = residents;
this->months = months;
this->owner = owner;
this->type = type;
Estate::EstateType Estate::getType() const
}
{
return this->type;
int Estate::getAge() const
}
{
return this->age;
int Estate::getHp() const
}
{
return this->hp;
int Estate::getResidents() const
}
{
return this->residents;
int Estate::getMonths() const
}
{
return this->months;
QString Estate::getOwner() const
}
{
return this->owner;
}
