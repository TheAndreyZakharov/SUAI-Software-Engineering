#include <iostream>
using namespace std;

#include "libs/lib.h"
#include <cmath>
#include <time.h>
#include <fstream>
#include <cctype>

#include "libs/simple_char.h"

#include "fstream_files.h"

char *get_file_name(const char *promt = "", const char *error_promt = "", bool new_file = false) {

  ifstream input_file;

  int len;
  char *input_file_name;

  bool ok = false;
  while (!ok) {
    cout << promt;
    input_file_name = get_string(&len);
    if (len > 0) {
      ok = true;

      input_file.open(input_file_name);

      if (!input_file.good()) {
        if (new_file) {
          ofstream ost(input_file_name);
        } else {
          cout << error_promt << endl;
          ok = false;
        }

      }

      input_file.close();

    }
  }

  return input_file_name;
}

// функция для подсчёта слов
void check_words(char *input_file_name, char *output_file_name, char *str, int len, bool data = false) {

  ifstream input_file;
  ofstream output_file;

  // открываем файлы
  input_file.open(input_file_name);
  output_file.open(output_file_name);

  char c;

  if (data) {
    draw_line(20);
    cout << "Отладочная информация." << endl;
    draw_line(20);
  }

  int find_count = 0;
  int find_index = 0;

  // цикл по всему файлу
  while (input_file) {

    // берём из файла 1 символ
    c = input_file.get();

    // если встречаем конец предложения, то записываем в него количество слов и обнуляем переменные для подсчёта
    if (c == '.' || c == '?' || c == '!') {
      if (data) cout << c << "(" << find_count << ") ";
      output_file << c << "(" << find_count << ") ";
      find_count = 0;

    } else {
      // в остальных случаях ищем слова
      if (str[find_index] == c) {
        // если слово полностью совпадает, то обновляем счётсчик
        if (find_index >= (len - 1)) {
            find_index = 0;
            find_count++;
        } else {
          find_index++;
        }
      } else {
        find_index = 0;
      }
      //
      output_file << c;
    }
  }

  input_file.close();
  output_file.close();

}

int main() {
  system("chcp 65001");

  //clear_scr();

  char *input_file_name;
  char *output_file_name;

  // вводим имена файлов (с проверкой)
  input_file_name = get_file_name("Имя входного файла: ", "Невозможно прочитать файл. Возможно его не существует.");
  output_file_name = get_file_name("Имя выходного файла: ", "Невозможно записать или создать файл.", true);

  draw_line(20);
  int len;
  // вводим слово для поиска
  char *str = check_char(&len, "Слово для поиска: ");

  // подсчитываем найденые слова
  check_words(input_file_name, output_file_name, str, len, false);

  draw_line(20);

  cout << "В файл " << output_file_name << " был успешно записан результат." << endl;

  return 0;
}
