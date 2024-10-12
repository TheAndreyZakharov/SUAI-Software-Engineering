
#include <iostream>
#include <string>
using namespace std;

#define COUNT_MONTH 12

// спискок с количеством дней в месяцах
int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// проверка на корректность даты
bool check_date(int day, int month) {
  if (month < 1 || month > 12)
    return false;
  if (day > days_in_month[month - 1] || day < 1)
    return false;
  return true;
}
