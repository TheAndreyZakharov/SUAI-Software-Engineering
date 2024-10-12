#include <iostream>
#include <cmath>

// Подсчитать сумму всех элементов, имеющих положительные значения
int get_sum_pol(int* arr, int size) {
  int sum = 0;

  for (int i = 0; i < size; i++) {
    if (arr[i] > 0)
      sum += arr[i];
  }

  return sum;
}

// Подсчитать количество элементов с чётными значениями
void get_count_chet(int count) {
  if (count > 0) {
    cout << "Количество чётных элементов: " << count << endl;
  } else
    cout << "В массиве нет положительных элементов." << endl;
}

// поверка ввода
double read_double() {
    double a;
    while (!(cin >> a) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Неверное введенное значение, попробуйте еще: ";
    }
    return a;
}
