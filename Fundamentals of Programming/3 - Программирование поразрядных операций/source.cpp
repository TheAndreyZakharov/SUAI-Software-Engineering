#include <iostream>
#include "lib.h"
#include "memory.h"
#include <windows.h>
using namespace std;

int main() {
	// смена кодировки
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int o = 0;
	int p = 0;
	int l = 0;

	draw_line(20);

	// вводим числа
	cout << "Идентификатор владельца блока: ";
	o = read_int();

	cout << "Признак программного блока: ";
	p = read_int();

	cout << "Размер блока: ";
	l = read_int();

	draw_line(20);

	// собираем
	unsigned short z = code(o, p, l);

	// выводим собранное число
	cout << "Блок управления памятью: 0x" << hex << z << endl;

	return 0;
}

