#ifndef CARSUSE_H
#define CARSUSE_H
#include <QObject>
#include <caruse.h>
class carsuse : public QObject//базовым классом является класс QOBJECT
{
    Q_OBJECT
public:
    explicit carsuse(QObject *parent = nullptr);
    ~carsuse();
    void undo();//функция манипулирует над actualdata добавляя в нее значение или null
    bool hasCarsuse();//наличие элементов в коллекции
    caruse *getActualData();//функция возвращающая последний элемент коллекции
    void add(caruse *value);//добавление элемента в коллекцию
private:
    QList<caruse *> array;//список в котором храняться элементы
    caruse *actualData;//последний элемент коллекции
signals:
    void notifyObservers();//сигнал наблюдателю
};
#endif // CARSUSE_H
