#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <iomanip>
#include "lib.h"

using namespace std;

double ftab(double a, double b, double c, double x) {
    if (((x + 10) < 0) && (b != 0)) {
        return a * pow(x, 2) - c * x + b;
    }
    else if (((x + 10) > 0) && (b == 0)) {
        return (x - a) / (x - c);
    }
    else {
        return (-x) / (a - c);
    }
}

int main() {
    // смена кодировки
    system("chcp 65001");

    double a = 0;
    double b = 0;
    double c = 0;

    double xMin = 0;
    double xMax = 0;
    double dx = 0;

    draw_line(20);

    // вводим числа
    cout << "a = ";
    a = read_double();

    cout << "b = ";
    b = read_double();

    cout << "c = ";
    c = read_double();

    draw_line(20);

    // ввод шага с проверкой на диапазон
    while (true) {
        cout << "xMin = ";
        xMin = read_double();

        cout << "xMax = ";
        xMax = read_double();

        if (xMin == xMax) {
            cout << "Диапазон числа одинаковый" << endl;
            draw_line(20);
        }
        else break;

    }

    // ввод шага с проверкой на его размер
    while (true) {
        cout << "dx = ";
        dx = abs(read_double());

        if (((xMin < xMax) ? (xMax - xMin) : (xMin - xMax)) < dx) {
            cout << "Шаг слишком маленький" << endl;
        }
        else break;
    }


    draw_line(20);

    double y = 0;
    // вывод шапки таблицы
    cout << "| " << setw(7) << "X | " << setw(11) << "Y |\n";
    draw_line(20);

    double x = xMin;

    // цикл while для того чтобы его можно было развернуть
    while (((xMin < xMax) ? (x < xMax + dx) : (x > xMax - dx))) {

        // наша функция
        y = ftab(a, b, c, x);

        // после каждого шага вычисляем шаг
        cout << "| " << setw(4) << x << " | " << setw(8) << (isinf(y) ? 0 : (isnan(y) ? 0 : y)) << " |\n";

        // каждую итерацию цикла обновляем счётсчик
        x += (xMin < xMax) ? (dx) : (-dx);
        /*
          (a == b)? b: a;

          это выражение можно представить так:

          if (a == b) {
            return b;
          } else {
            return a;
          }
        */
    }

    draw_line(20);

    return 0;
}

