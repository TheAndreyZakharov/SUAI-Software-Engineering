#include "carsuse.h"
carsuse::carsuse(QObject *parent)
: QObject{parent}
{
actualData = nullptr;
carsuse::~carsuse()
}
{
if(actualData){//удаление actualdata
delete actualData;
actualData=nullptr;
}
array.clear();//удаление о очистка array
qDeleteAll(array);
}
bool carsuse::hasCarsuse(){
return !array.empty();//в коллекции есть элементы
}
caruse *carsuse::getActualData(){
return array.back();
}
void carsuse::add(caruse *value){
array.append(value);//добавление элемента в коллекцию
}
void carsuse::undo(){
if(!hasCarsuse()||(array.size()==1)){
actualData=nullptr;//если в коллекции нет элементов actualdata равна nullptr
}
else {//если есть элементы то заполняем actualdata значением и отправляем сигнал наблюдателю
actualData=getActualData();
array.removeLast();
emit notifyObservers();//сигнал уведомляющий наблюдателя
}
}
