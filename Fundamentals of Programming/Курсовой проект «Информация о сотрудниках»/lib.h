#include <iostream>
#include <string>
using namespace std;

// функция рисующая полосу для разделения
void draw_line(int size) {
  for (int i = 0; i < size; i++)
    cout << '-';
  cout << endl;
}

// проверка на ввод числа
int read_int(const char* promt = "") {
	int n;
	cout << promt;
	while (!(cin >> n) || (cin.peek() != '\n')) {
		cin.clear();
		while (cin.get() != '\n');
		cout << "Ошибка ввода. Повторите ввод. " << endl << promt;
	}
	return n;
}

// вспомог. функция для проверки строки на пустоту
bool isEmpty(const string& str) {
  return str.find_first_not_of(' ') == str.npos || str.empty();
}

// проверка на ввод строки
string read_string(const char* promt = "") {
	string n;
	cout << promt;
  while (true) {
		getline(cin, n);

		if (isEmpty(n))
			cout << "Вы ввели пустую строку. Повторите ввод." << endl << promt;
		else break;
	}
	return n;
}

// поднимает первые буквы а остальные наоборот
string fix_name(string name) {
	name[0] = toupper(name[0]);
	for (int i = 1; i < name.length(); i++) {
		name[i] = tolower(name[i]);
	}
	return name;
}

// проверка на число
bool check_str_to_int(string x) {
	for (int i = 0; i < x.length(); i++) {
		if (!isdigit(x[i]))
			return false;
	}
	return true;
}
