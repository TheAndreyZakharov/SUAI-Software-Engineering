#include <iostream>
using namespace std;

#include <cmath>

#include "arr_vec.h"

int main() {
    draw_line(60);
    // смена кодировки
    system("chcp 65001");
    
    // srand(time(NULL));
    
    Arr_vec arr_vec(10);
    cout << "Сгенерированный вектор." << endl;
    arr_vec.show();
    
    arr_vec.devide_all();
    cout << "Поделили все элементы массива на 2" << endl;
    arr_vec.show();
    
    if (arr_vec.swap_els(2)) {
        cout << "Зеркально обменяли 2 первых и 2 последных элемента." << endl;
        arr_vec.show();
    } else {
        cout << "Невозможно обменять 2 первых и 2 последних элемента вектора, т.к. он мал." << endl;
    }
    
    arr_vec.chenage_on_zero();
    cout << "Заменили элементы массива (всё что меньше 10 заменить на 0)." << endl;
    arr_vec.show();
    
    return 0;
}
