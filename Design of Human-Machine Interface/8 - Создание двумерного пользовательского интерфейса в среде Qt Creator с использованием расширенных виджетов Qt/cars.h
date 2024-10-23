#ifndef CARS_H
#define CARS_H
#include <QObject>
#include <car.h>
class cars : public QObject//базовым классом является класс QOBJECT
{
    Q_OBJECT
public:
    explicit cars(QObject *parent = nullptr);
    ~cars();
    void undo();//функция манипулирует над actualdata добавляя в нее значение или null
    bool hasCars();//наличие элементов в коллекции
    car *getActualData();//функция возвращающая последний элемент коллекции
    void add(car *value);//добавление элемента в коллекцию
    QList<car *> array;//список в котором храняться элементы
private:
    car *actualData;//последний элемент коллекции
signals:
    void notifyObservers();//сигнал наблюдателю
};
#endif // CARS_H
