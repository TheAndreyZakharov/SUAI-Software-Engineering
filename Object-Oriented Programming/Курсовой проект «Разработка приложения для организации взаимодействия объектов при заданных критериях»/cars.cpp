#include "cars.h"
cars::cars(QObject *parent)
    : QObject{parent}
{
    actualData = nullptr;
}
cars::~cars()
{
    if(actualData){//удаление actualdata
        delete actualData;
        actualData=nullptr;
    }
    array.clear();//удаление о очистка array
    qDeleteAll(array);
}
bool cars::hasCars(){
    return !array.empty();//в коллекции есть элементы
}
    car *cars::getActualData(){
        return array.back();
    }
void cars::add(car *value){
    array.append(value);//добавление элемента в коллекцию
}
void cars::undo(){
    if(!hasCars()||(array.size()==1)){
        actualData=nullptr;//если в коллекции нет элементов actualdata равна nullptr
    }
    else {//если есть элементы то заполняем actualdata значением и отправляем сигнал наблюдателю
        actualData=getActualData();
        array.removeLast();
        emit notifyObservers();//сигнал уведомляющий наблюдателя
    }
}
