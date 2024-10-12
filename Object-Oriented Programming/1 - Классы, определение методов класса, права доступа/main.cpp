/*
  6 вариант (16 mod 10)

    Поле left - вещественное число, левая граница диапазона. Поле right - вещественное
  число, правая граница диапазона. Пара этих числе представляет полуоткрытый интервал
  [left,right). Реализовать класс, в котором предусмотреть метод rangecheck() - проверку
  заданного числа на принадлежность диапазону.

*/

#include <iostream>
using namespace std;

#include "libs/lib.h"
#include <cmath>
#include <time.h>

// проверка ввода
#include "libs/simple_char.h"
#include "libs/input_validation.h"

#include "range.h"

int main() {
    // смена кодировки
    setlocale(LC_ALL, "Russian");

    Range range;

  // вводим диапазон
  double left = read_value("Левая граница: ");
  double right = read_value("Правая граница: ");

  // переворачиваем диапазон если пользователь его не правльно ввёл
  if (left > right) {
    double buf = left;
    left = right;
    right = buf;
  }

  // устанавливаем диапазон
  range.rangeset(left, right);

  // вывод введённых чисел
  draw_line(20);
  cout << "Введёный диапазон" << endl;
  range.rangedraw();
  draw_line(20);

  bool range_status = range.rangecheck(
    read_value("Число для проверки диапазона: ", true, true, false)
  );

  // вывод результата
  if (range_status)
    cout << "Число входит в диапазон." << endl;

  else
    cout << "Число не входит в диапазон." << endl;

    return 0;
}
