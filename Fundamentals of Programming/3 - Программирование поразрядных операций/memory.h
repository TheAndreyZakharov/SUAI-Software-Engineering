#include <iostream>
#include <cmath> // для pow (возведение в степень)

using namespace std;

// функция для сбора в команду сложения
unsigned short code(int o, int p, int l) {
    if ( // проверка
        (o >= 0 && o < pow(2, 8)) &&
        (p >= 0 && p < pow(2, 1)) &&
        (l >= 0 && l < pow(2, 6))
        ) {
        // если всё хорошо то объеденяем числа
        return 0 | l << 0 | p << 6 | o << 8;
    }
    else {
        /*
          если числа не входят в диапазон
            (не помещаются в переменную, то выводим пользователю
            об этом сообщение и выходим из программы)
        */
        cout << "Числа не входят в диапазон" << endl;

        exit(0);
    }
}

void decode(unsigned short x) {
    /*
      >> - побитовый сдвиг
      &число - то сколько надо бит вытащить
    */
    int o = (x >> 8) & 0xFF;
    int p = (x >> 6) & 0x1;
    int l = (x >> 0) & 0x3F;

    draw_line(20);
    // выводим числа
    // dec -  вывести число в 10 системе счисления
    cout << dec << "Идентификатор владельца блока: " << o << endl;
    cout << dec << "Признак программного блока: " << p << endl;
    cout << dec << "Размер блока: " << l << endl;
    draw_line(20);
}
