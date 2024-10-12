
#include <iostream>
#include <string>
using namespace std;

// количество зодиаков
#define COUNT_ZODIACS 12

struct zodiac {
  int d1[2];
  int d2[2];
  string name;
};

// спискок всех задиков с датами
zodiac zodiac_list[]={
  {{21, 3},{20, 4},"Овен"},
  {{21, 4},{21, 5},"Телец"},
  {{22,05},{21, 6},"Близнецы"},
  {{22, 6},{22, 7},"Рак"},
  {{23, 7},{23, 8},"Лев"},
  {{24, 8},{23, 9},"Дева"},
  {{24, 9},{23,10},"Весы"},
  {{24,10},{22,11},"Скорпион"},
  {{23,11},{21,12},"Стрелец"},
  {{22,12},{20, 1},"Козерог"},
  {{21, 1},{19, 2},"Водолей"},
  {{20, 2},{20, 3},"Рыбы"}
};

// получить задиак по дате
string get_zodiak_by_data(int day, int month) {
  for (int i = 0; i < COUNT_ZODIACS; i++) {
    if (month == zodiac_list[i].d1[1] && day >= zodiac_list[i].d1[0] || month == zodiac_list[i].d2[1] && day <= zodiac_list[i].d2[0]) {
      return zodiac_list[i].name;
    }
  }
  return "";
}
