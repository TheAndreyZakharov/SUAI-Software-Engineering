
/*
  4 вариант ( (26 % 03) + 1 )

    Используя память, пропорциональную n, хранить массив целых чисел
  A, содержащий n элементов.
    Элементы массива A могут принимать случайные значения от
  -((n div 2) - 1) до (n div 2). То есть, если в массиве хранится 10 элементов, то
  эти элементы должны быть в диапазоне от -4 до 5.
    Разработать алгоритм, который осуществляет заполнение массива A
  случайными значениями, и по выбору пользователя выполняет одну из двух
  функций.

  - Подсчитать сумму всех элементов, имеющих положительные значения
  - Подсчитать количество элементов с четными значениями

*/

#include <iostream>
using namespace std;

#include <cmath>
#include <time.h>

#include "functions.h"

int main() {
    // смена кодировки
    setlocale(LC_ALL, "Russian");

  //рандом
  srand((unsigned int)time(NULL));

  int size = 0;

  // ввод размера массива
  while (true) {
    cout << "Размер массива: ";
    size = read_double();
    if (size > 0)
      break;

    else
      cout << "Размер массива должен быть больше 0." << endl;
  }

  // создаём массив
  int* arr = (int*)malloc(size * sizeof(int));

  // диапазон чисел для заполнения через рандом
  int rand_min = - ((size / 2) - 1);
  int rand_max = size / 2;

  // заполняем
  for (int i = 0; i < size; i++) {
    arr[i] = rand_min + (rand() % ( rand_max - rand_min + 1 ) ); 
  }

  int num;
  bool run = true;

  int sum;
  int count;

  // вывод меню и информации о массиве
  cout << "Числа сгенерированны в диапазоне от " << rand_min << " до " << rand_max << endl;
  cout << "Массив: ";

  for (int i = 0; i < size; i++)
    cout << arr[i] << " ";
  cout << endl;


  cout << "1 - Подсчитать сумму всех элементов, имеющих положительные значения." << endl;
  cout << "2 - Подсчитать количество элементов с чётными значениями." << endl << endl;
  cout << "0 - Выход" << endl;

  // цикл для меню
  while (run) {

    // ввод пункта меню
    //num = read_value(" >> ", true, true, false);
    cout << " >> ";
    //scanf("%d", &num);
    num = read_double();

    switch (num) {
            

      // Подсчитать сумму всех элементов, имеющих положительные значения
      case (1):

        sum = get_sum_pol(arr, size);
        if (sum > 0) {
          cout << "Сумма положительных элементов: " << sum << endl;
        } else
          cout << "В массиве нет положительных элементов." << endl;

        break;

      // Подсчитать количество элементов с чётными значениями.
      case (2):

        count = 0;

        for (int i = 0; i < size; i++) {
          if (arr[i] % 2 == 0) count++;
        }

        get_count_chet(count);


        break;

      // выход
      case (0):

        run = false;
        break;
    }
  }


  free(arr);
    return 0;
}
