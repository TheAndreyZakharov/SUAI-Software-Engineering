

#include <iostream>
using namespace std;

#include <cmath>

#include "exception.h"
#include "array.h"

int main() {
    // смена кодировки
    system("chcp 65001"); // для VS заменить на setlocale(LC_ALL, "Russian");
    
    // размер массива (2 + 6)
    Array array(8); // вместо 8 можно указать любой размер для массива
    array.show();
    
    try {
        cout << "Минимальный элемент массива: " << array.get_arr()[array.get_min()] << endl;
        
    } catch (MyException &ex) {
        // cout << "Мы поймали " << ex.what() <<endl;
    }
    
    cout << "Сумма между первым положительным и последним: " << array.get_sum() << endl;
    
    array.my_sort();
    array.show();
    
    return 0;
}
