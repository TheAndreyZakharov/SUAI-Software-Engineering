/*
 6 вариант
 Определите класс Student (Студент). Этот класс должен иметь следующие
 поля: name (имя), surname (фамилия), year (год поступления в вуз). Класс должен иметь
 метод getFullName(), с помощью которого можно вывести одновременно имя и фамилию
 студента. Также класс должен иметь метод getCourse(), который будет выводить текущий
 курс студента (от 1 до 5). Курс вычисляется так: нужно от текущего года отнять год
 поступления в вуз. Текущий год получите самостоятельно.
 */

#include <iostream>
using namespace std;

#include <string.h>

#include "student.h"

int main() {
    // смена кодировки
    setlocale(LC_CTYPE, "Russian");
    
    Student student_default;
    cout << "По умолчанию" << endl;
    student_default.getFullName();
    student_default.getCourse();
    
    Student student_args("Дмитрий", "Сугак", 2018);
    cout << "С аргументами" << endl;
    student_args.getFullName();
    student_args.getCourse();
    
    Student student_copy = student_args;
    cout << "Копирование" << endl;
    student_copy.getFullName();
    student_copy.getCourse();
    //разрушение объектра класса -> выходит из зоны видимости -> освобождение ресурсов выделенных в классе
    //объект класса вне зоны видимости -> уничтожение в обратном порядке
    return 0;
}
