#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include "lib.h"
#include <cmath>

// функции для лабы (get_count_positive_els, sum_els_from_last_zero, get_new_arr)
#include "functions.h"

int main() {
    // смена кодировки
    system("chcp 65001");
    setlocale(LC_ALL, "Russian");
    draw_line(20);

    // ввод размера массива с проверкой
    int size;
    while (true) {
        cout << "Введите размер массива: ";
        size = read_int();

        if (size > 0) {
            break;
        }
        else {
            cout << "Массив в данном задании не может быть меньше 1 элемента." << endl;
        }
    }

    // создаём массив
    double* arr = (double*)malloc(size * sizeof(double));

    // вводим массив
    for (int i = 0; i < size; i++) {
        cout << "array [" << i << "] = ";
        arr[i] = read_double();
    }

    draw_line(20);
    draw_float_array(arr, size); // выводим массив
    draw_line(20);

    // получение и вывод количества в массиве положительных элементов
    int count_positive_els = get_count_positive_els(arr, size);
    if (count_positive_els > 0)
        cout << "Положительных элементов в массиве: " << count_positive_els << endl;
    else
        cout << "В массиве нет положительных элементов." << endl;

    // получение и вывод суммы элементов после 0
    int summ = sum_els_from_last_zero(arr, size);
    if (summ > -1)
        cout << "Сумма элементов массива, расположенных после последнего элемента, равного 0: " << summ << endl;
    else
        cout << "В массиве нет элементов равных 0." << endl;

    double* new_arr = get_new_arr(arr, size);

    draw_line(20);
    draw_float_array(new_arr, size); // выводим новый массив
    draw_line(20);

    // удаление массивов
    free(arr);
    free(new_arr);

    return 0;
}
