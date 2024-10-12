/*
 4 вариант
 Найти количество различных чисел среди элементов массива
 Простым извлечением
 Использовать неупорядоченный массив A, содержащий n
 целочисленных элементов. Величина n определяется по согласованию с
 преподавателем. Дополнительно в программе должны быть реализованы
 следующие функции:
 1) Поиск элемента либо по его порядковой позиции, либо по его
 содержимому;
 2) Добавление/удаление элемента с последующей пересортировкой
 последовательности;
 3) В программе должен быть реализован подсчет количества
 сравнений и перестановок, при осуществлении сортировки.
 */

#include <iostream>
using namespace std;

#include "lib.h"
#include <cmath>
#include <time.h>
#include <iomanip>

// проверка ввода
#include "simple_char.h"
#include "input_validation.h"

#include "array.h"

#include "sort.h"

int menu() {
    int id;
    while (true) {
        draw_line(30);
        cout << "1) добавить элемент в массив" << endl;
        cout << "2) удалить элемент из массива" << endl;
        cout << "3) вывести массив" << endl;
        cout << "4) сортировать массив" << endl;
        cout << "5) Найти количество различных элементов" << endl;
        cout << "0) Выход" << endl;
        id = read_value(" >>> ", false, false, false);
        if (id >= 0 && id <= 5) {
            return id;
        } else {
            cout << "Этого нет в меню" << endl;
        }
    }
}

int main() {
    // смена кодировки
    system("chcp 65001");
    draw_line();
    
    int size = read_value("Размер массива: ", false, false, false);
    
    Array array(size, true, true);
    
    int menu_i;
    while (true) {
        menu_i = menu();
        
        switch (menu_i) {
            case (0):
                return 0;
                break;
                
            case (1):
                array.add(read_value("Добавляемый элемент: ", false, false, false));
                break;
                
            case (2): {
                int returned = array.pop(read_value("Id удаляемого элемена: ", false, false, false));
                cout << "Удалённый элемент: " << returned << endl;
                break;
            }
                
            case (3):
                array.draw("Массив: ");
                break;
                
            case (4):
                array.sort_arr();
                break;
                
            case (5):
                cout << "Количество различных элементов: " << array.dif_els() << endl;
                break;
        }
        
    }
    return 0;
}
