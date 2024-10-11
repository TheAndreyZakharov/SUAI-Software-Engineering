#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "lib.h"
#include "memory.h"
#include <windows.h>
using namespace std;

int main() {
	// смена кодировки
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	unsigned int x;

	draw_line(20);

	cout << "Введите команду сложения (16-ричное число от 0 до 0xFFFF): ";
	cin >> hex >> x;

	decode(x);

	return 0;
}
