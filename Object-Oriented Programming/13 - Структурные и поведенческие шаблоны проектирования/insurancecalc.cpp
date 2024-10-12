//аналогичны luxurioscalc.cpp/plane.cpp/speccalc.cpp
#include "insurancecalc.h"
insurancecalc::insurancecalc(QObject *parent)
: QObject{parent}
int insurancecalc::getCost(Estate *value)
{
}
{
if (value->getAge() == 0) //стаж
{
if (value->getResidents() == 1) //кол-во людей в страховке
{
if (value->getHp() <= 100) //кол-во лс
return ((250 + 100 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((250 + 100 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((250 + 100 + value->getHp()*5) * (value->getMonths()/6))*20;
}
if (value->getResidents() >= 2 && value->getResidents() <= 5) //кол-во людей в страховке
{
if (value->getHp() <= 100) //кол-во лс
return ((250 + 250 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((250 + 250 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((250 + 250 + value->getHp()*5) * (value->getMonths()/6))*20;
if (value->getResidents() > 5) //кол-во людей в страховке
}
{
if (value->getHp() <= 100) //кол-во лс
return ((250 + 500 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((250 + 500 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((250 + 500 + value->getHp()*5) * (value->getMonths()/6))*20;
}
}
if (value->getAge() <= 1) //стаж
{
if (value->getResidents() == 1) //кол-во людей в страховке
{
if (value->getHp() <= 100) //кол-во лс
return ((value->getAge()*150 + 100 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((value->getAge()*150 + 100 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((value->getAge()*150 + 100 + value->getHp()*5) * (value->getMonths()/6))*20;
}
if (value->getResidents() >= 2 && value->getResidents() <= 5) //кол-во людей в страховке
{
if (value->getHp() <= 100) //кол-во лс
return ((value->getAge()*150 + 250 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((value->getAge()*150 + 250 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((value->getAge()*150 + 250 + value->getHp()*5) * (value->getMonths()/6))*20;
if (value->getResidents() > 5) //кол-во людей в страховке
}
{
if (value->getHp() <= 100) //кол-во лс
return ((value->getAge()*150 + 500 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((value->getAge()*150 + 500 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((value->getAge()*150 + 500 + value->getHp()*5) * (value->getMonths()/6))*20;
}
}
if (value->getAge() == 2) //стаж
{
if (value->getResidents() == 1) //кол-во людей в страховке
{
if (value->getHp() <= 100) //кол-во лс
return ((value->getAge()*50 + 100 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((value->getAge()*50 + 100 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((value->getAge()*50 + 100 + value->getHp()*5) * (value->getMonths()/6))*20;
if (value->getResidents() >= 2 && value->getResidents() <= 5) //кол-во людей в страховке
}
{
if (value->getHp() <= 100) //кол-во лс
return ((value->getAge()*50 + 250 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((value->getAge()*50 + 250 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((value->getAge()*50 + 250 + value->getHp()*5) * (value->getMonths()/6))*20;
if (value->getResidents() > 5) //кол-во людей в страховке
}
{
if (value->getHp() <= 100) //кол-во лс
return ((value->getAge()*50 + 500 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((value->getAge()*50 + 500 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((value->getAge()*50 + 500 + value->getHp()*5) * (value->getMonths()/6))*20;
}
if (value->getAge() == 3) //стаж
}
{
if (value->getResidents() == 1) //кол-во людей в страховке
{
if (value->getHp() <= 100) //кол-во лс
return ((value->getAge()*30 + 100 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((value->getAge()*30 + 100 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((value->getAge()*30 + 100 + value->getHp()*5) * (value->getMonths()/6))*20;
if (value->getResidents() >= 2 && value->getResidents() <= 5) //кол-во людей в страховке
}
{
if (value->getHp() <= 100) //кол-во лс
return ((value->getAge()*30 + 250 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((value->getAge()*3050 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((value->getAge()*30 + 250 + value->getHp()*5) * (value->getMonths()/6))*20;
if (value->getResidents() > 5) //кол-во людей в страховке
}
{
if (value->getHp() <= 100) //кол-во лс
return ((value->getAge()*30 + 500 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((value->getAge()*30 + 500 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((value->getAge()*30 + 500 + value->getHp()*5) * (value->getMonths()/6))*20;
}
}
if (value->getAge() == 4) //стаж
{
if (value->getResidents() == 1) //кол-во людей в страховке
{
if (value->getHp() <= 100) //кол-во лс
return ((value->getAge()*10 + 100 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((value->getAge()*10 + 100 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((value->getAge()*10 + 100 + value->getHp()*5) * (value->getMonths()/6))*20;
if (value->getResidents() >= 2 && value->getResidents() <= 5) //кол-во людей в страховке
}
{
if (value->getHp() <= 100) //кол-во лс
return ((value->getAge()*10 + 250 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((value->getAge()*10 + 250 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((value->getAge()*10 + 250 + value->getHp()*5) * (value->getMonths()/6))*20;
if (value->getResidents() > 5) //кол-во людей в страховке
}
{
if (value->getHp() <= 100) //кол-во лс
return ((value->getAge()*10 + 500 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((value->getAge()*10 + 500 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((value->getAge()*10 + 500 + value->getHp()*5) * (value->getMonths()/6))*20;
}
if (value->getAge() >= 5) //стаж
}
{
if (value->getResidents() == 1) //кол-во людей в страховке
{
if (value->getHp() <= 100) //кол-во лс
return ((5 + 100 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((5 + 100 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((5 + 100 + value->getHp()*5) * (value->getMonths()/6))*20;
if (value->getResidents() >= 2 && value->getResidents() <= 5) //кол-во людей в страховке
}
{
if (value->getHp() <= 100) //кол-во лс
return ((5 + 250 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((5 + 250 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((5 + 250 + value->getHp()*5) * (value->getMonths()/6))*20;
if (value->getResidents() > 5) //кол-во людей в страховке
}
{
if (value->getHp() <= 100) //кол-во лс
return ((5 + 500 + value->getHp()*3) * (value->getMonths()/6))*20;
if (value->getHp() > 100 && value->getHp() <= 150) //кол-во лс
return ((5 + 500 + value->getHp()*4) * (value->getMonths()/6))*20;
if (value->getHp() > 150) //кол-во лс
return ((5 + 500 + value->getHp()*5) * (value->getMonths()/6))*20;
}
}
}
}
