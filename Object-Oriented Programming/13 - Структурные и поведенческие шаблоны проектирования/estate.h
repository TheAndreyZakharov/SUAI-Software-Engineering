// Листинг файла estate.h
#ifndef ESTATE_H
#define ESTATE_H
#include <QObject>
class Estate : public QObject
{
Q_OBJECT
public:
enum EstateType {
ECONOM,
LUXURIOUS,
SPEC,
PLANE
};
Estate(const int age, const int hp, const int residents,
const int months, const EstateType type, const QString owner);
explicit Estate(QObject *parent = nullptr);
EstateType getType() const;
int getAge() const;
int getHp() const;
int getResidents() const;
int getMonths() const;
QString getOwner() const;
private:
int age;
int hp;
int residents;
int months;
EstateType type;
QString owner;
};
#endif // ESTATE_H
