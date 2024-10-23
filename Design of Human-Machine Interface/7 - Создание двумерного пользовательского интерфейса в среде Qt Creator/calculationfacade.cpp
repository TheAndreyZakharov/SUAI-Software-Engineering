#include "calculationfacade.h"
CalculationFacade::CalculationFacade(QObject *parent)
    : QObject{parent}
{
}
int CalculationFacade::getCost(car *value) {
// Путь создания объектов:CalcFactory->***Factory->***Calc; ***Calc вызывает функцию getCost()
int cost;//переменная с ценой
switch (value->getType())//определяем тип комплектации
    {
    case car::CarType::STANDARD:{
    //создается класс фабрика
        CalcFactory * standard_factory = new StandardFactory; // выделяем память под объект класса StandardFactory
        //создание объекта фабричного класса и вычисление стоимсоти
        cost = standard_factory->fabrica()->getCost(value); // создаем объект и расчитываем его стоимость
        delete standard_factory; // оцищаем память
        break;
    }
    case car::CarType::COMFORT:{
        CalcFactory * comfort_factory = new ComfortFactory; // выделяем память под объект класса ComfortFactory
        cost = comfort_factory->fabrica()->getCost(value); // создаем объект и расчитываем его стоимость
        delete comfort_factory; // очищаем память
        break;
    }
    case car::CarType::LUXURY:{
        CalcFactory * luxury_factory = new LuxuryFactory; // выделяем память под объект класса LuxuryFactory
        cost = luxury_factory->fabrica()->getCost(value); // создаем объект и расчитываем его стоимость
        delete luxury_factory; // очищаем память
        break;
    }
    case car::CarType::ELECTRIC:{
        CalcFactory * electric_factory = new ElectricFactory; // выделяем память под объект класса ElectricFactory
        cost = electric_factory->fabrica()->getCost(value); // создаем объект и расчитываем его стоимость
        delete electric_factory; // очищаем память
        break;
    }
    default:
        cost = -1;
        break;
    }
    return cost;
}
