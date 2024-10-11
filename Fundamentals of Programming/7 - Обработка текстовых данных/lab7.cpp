#include <iostream>
using namespace std;

#include "libs/lib.h"
#include <cmath>
#include <time.h>

// проверка ввода
#include "libs/simple_char.h"

#include "more_char.h"
char *get_string(int *len) {
    *len = 0;
    int capacity = 1;
    char *s = (char*) malloc(sizeof(char));
    char c = getchar();
    while (c != '\n') {
        s[(*len)++] = c;
        if (*len >= capacity) {
            capacity *= 2;
            s = (char*) realloc(s, capacity * sizeof(char));
        }
        c = getchar();
    }
    s[*len] = '\0';
    return s;
}

int str_find(char *str_1, int len_1, char *str_2, int len_2) {
  // флаг состояния поиска
  bool find = true;

  // для 1 строки
  for (int i = 0; i < len_1; i++) {
    find = true;

    // цикл для 2 строки
    for (int j = 0; j < len_2; j++)

      // если нашли одинаковые символы, то идём на следующую итерацию цикла
      if (str_1[i] == str_2[j]) {
        find = false;
        break;
      }

    // если есть символ который мы не нашли, то возвращаем его
    if (find) return i;
  }

  // если строки одинаковые (по набору символов), то возвращаем -1
  return -1;
}


// функция для ввода строки и проверки её
char *check_char(int *len, const char *promt = "") {
  (*len) = 0;
  char *char_str;

  // ввод строки
  while (true) {
    cout << promt;
    char_str = get_string(&(*len));

    if ((*len) > 0) {
      // проверка на пробелы (строка не должна состоять из пробелов)
      bool space_check = false;
      for (int i = 0; i < (*len); i++)
        if (!isspace(char_str[i])) {
          space_check = true;
          break;
        }

      if (space_check)
        break;
      else
        cout << "Строка не может состоять из пробелов." << endl;

    } else {
      cout << "Вы ввели пустую строку." << endl;
    }
  }

  return char_str;
}

int main() {
    // смена кодировки
  system("chcp 65001");

  // очистка терминала
  //clear_scr();

  // здесь будет храниться длинна вводимых строк
  int len_1, len_2;

  // вводим строки
  char *char_str_1 = check_char(&len_1, "Введите первую строку: ");
  char *char_str_2 = check_char(&len_2, "Введите вторую строку: ");

  draw_line(20);

  //
  int find_index = str_find(char_str_1, len_1, char_str_2, len_2);

  if (find_index == -1) {
    cout << "Все символы входят во вторую строку." << endl;
  } else {
    cout << "Первый символ который мы не нашли: " << char_str_1[find_index] << endl;
    cout << "Его индекс в первой строке: " << find_index << endl;
  }

  // очищаем память
  free(char_str_1);
  free(char_str_2);

    return 0;
}
