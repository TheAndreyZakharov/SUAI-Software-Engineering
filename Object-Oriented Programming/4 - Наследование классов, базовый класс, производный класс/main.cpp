/*
 9 вариант (19 mod 10) + 1
 
 Создать класс Работник фирмы(фио, образование, Год поступления на
 работу, оклад). В классе должен быть метод вывода данных о работнике. На основе класса
 работника фирмы создать производные классы Стажер(должность, продолжительность
 испытательного строка, надбавка за прилежность), Руководящий работник(наименование
 отдела, количество подчиненных, надбавка за руководство), Директор(количество
 отделов, надбавка). В производных классах предусмотреть методы для расчета зарплаты и
 вычисления стажа работы, для Директора – подсчет количества подчиненных.
 
 */

#include <iostream>
using namespace std;

#include <cmath>

#include "Employee.h"
#include "Intern.h"
#include "Leading_worker.h"
#include "Director.h"

namespace global {
int count_count_subordinates = 0;
}

// рисует линию в терминале
void draw_line(int size = 20) {
    for (int i = 0; i < size; i++)
        cout << '-';
    cout << endl;
}

int main() {
    // смена кодировки
    system("chcp 65001");
    
    // Стажер
    Intern intern((char*)"test1", 2013, 13000, (char*)"тест", 100, 1000);
    intern.info();
    
    draw_line();
    
    // Руководящий работник
    Leading_worker leading_worker((char*)"test2", 2020, 20000, (char*)"Завод", 10);
    leading_worker.info();
    
    draw_line();
    
    // Директор
    Director director((char*)"test3", 2002, 30000, 2, 100);
    director.info();
    
    return 0;
}
