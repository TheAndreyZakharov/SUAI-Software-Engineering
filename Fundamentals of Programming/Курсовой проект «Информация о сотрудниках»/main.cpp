#define _CRT_SECURE_NO_WARNINGS

//Работа с линейным однонаправленным списком
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h> //выделение, преобразование
#include <crtdbg.h> //отслеживание утечек

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW
#endif
#endif

#include <iostream>
#include <string>
#include <set>
#include <iomanip>
#include <fstream>
#include <windows.h>

#include "lib.h"
#include "zodiaks.h"
#include "date.h"

using namespace std;


struct ZNAK {
	string name; // имя
	string surname; // фамилия
	string zodiak; // знак зодиака
	int birthday[3]; // дата рождения
};

struct List {
	ZNAK data; // информационное поле (данные) узла списка
	List* next; // указатель на следующий узел списка
};

// вспомог. функция для вывода одной записи
void OutLine(ZNAK d, ostream& os, int id, bool for_file = false) {
	if (for_file) {
		os << left << d.name << " " << d.surname << " " << d.zodiak << " "
			<< d.birthday[0] << " " << d.birthday[1] << " " << d.birthday[2] << endl;
	} else {
		os << left << "" << id << " " << d.name << " " << d.surname << " " << d.zodiak << " "
			<< d.birthday[0] << "." << d.birthday[1] << "." << d.birthday[2] << endl;
	}

}

// Редактирование списка
void UpdateElem(List** ptr, ZNAK r2) {
	List* p = *ptr;
	p->data.birthday[0] = r2.birthday[0];
	p->data.birthday[1] = r2.birthday[1];
	p->data.birthday[2] = r2.birthday[2];
	p->data.name = r2.name;
	p->data.surname = r2.surname;
	p->data.zodiak = r2.zodiak;
}

// Добавление элемента в конец списка
void AddElem(List** begin, List** cur, ZNAK elem) {
	List* p = new List;
	p->data = elem; //проверка, является ли список пустым
	if (*begin == NULL) {
		p->next = NULL;
		*begin = p;
	} else {
		p->next = (*cur)->next;// или p->next = NULL;
		(*cur)->next = p;
	}
	*cur = p;
}

// Добавление элемента в начало списка
void AddFirstElem(List** begin, ZNAK elem) {
	List* p = new List;
	p->data = elem; //проверка, является ли список пустым
	if (*begin == NULL) {
		p->next = NULL;
	} else {
		p->next = *begin;
	}
	*begin = p;
}

// Вывод элементов списка на экран
void PrintList(List* begin, ostream& os, bool for_file = false) {
	List* p = begin;
	int i = 0;
	while (p != NULL) {
		OutLine(p->data, os, i, for_file);
		p = p->next;
		i++;
	}
}

// Поиск элемента в списке по имени, знаку зодиака, дате рождения
void FindElem(List* begin, ZNAK elem, bool name = false, bool surname = false, bool zadiak = false, bool birthday = false) {
	List* p = begin;
	int i = 0;
	bool ok = false;
	while (p != NULL) {
		ok = false;

		// по имени
		if (name && (p->data.name == elem.name)) ok = true;

		// по фамилии
		if (surname && (p->data.surname == elem.surname)) ok = true;

		// по зодиаку
		if (zadiak && (p->data.zodiak == elem.zodiak)) ok = true;

		// по дате
		if (birthday && ((p->data.birthday[0] == elem.birthday[0]) && (p->data.birthday[1] == elem.birthday[1]) && (p->data.birthday[2] == elem.birthday[2]))) ok = true;
		if (ok) {
			OutLine(p->data, cout, i);
		}
		p = p->next;
		i++;
	}
	//return p;
}

// Удаление элемента из списка
void DelElem(List** begin, List* ptrCur) {
	List* p;
	if (ptrCur == *begin) {
		// удаляем первый элемент
		*begin = (*begin)->next;
	} else {
		// устанавливаем вспомогательный указатель на элемент, предшествующий удаляемому
		p = *begin;
		while (p->next != ptrCur)
			p = p->next; // удаление элемента
		p->next = ptrCur->next;
	}
	delete ptrCur;
}

// получить размер списка
int GetSizeList(List* begin) {
	List* p = begin;
	int size = 0;
	while (p != NULL) {
		p = p->next;
		size++;
	}
	return size;
}

// получить элемент списка по ID
List* GetById(List* begin, int id) {
	List* p = begin;
	int i = 0;
	while (p != NULL) {
		if (i == id)
			return p;
		p = p->next;
		i++;
	}
	return NULL;
}

// Очистка памяти
void Free(List** begin) {
	if (*begin == 0)
		return;
	List* p = *begin;
	List* t;
	while (p) {
		t = p;
		p = p->next;
		delete t;
	}
	*begin = NULL;
}

// Ввод данных - фамилия, имя, знак зодиака и дата рождения
void inputData(ZNAK& r, bool write_name = true, bool write_surname = true, bool write_date = true) {
	string name, surname;
	cin.ignore();

	// фамилия
	if (write_surname) {
		surname = read_string("Фамилия: ");
		r.surname = fix_name(surname);
		r.surname = string(/*RUS*/(r.surname.c_str()));
	}
	// имя
	if (write_name) {
		name = read_string("Имя: ");
		r.name = fix_name(name);
		r.name = string(/*RUS*/(r.name.c_str()));
	}

	int day, month, year;
	// ввод даты
	if (write_date) {
		while (true) {
			cout << "Дата рождения." << endl;
			day = read_int("День: ");
			month = read_int("Месяц: ");
			year = read_int("Год: ");

			// проверка на корректность даты
			if (check_date(day, month)) {
				break;
			} else {
				cout << "Дата введена не корректно." << endl;
			}
		}

		r.birthday[0] = day;
		r.birthday[1] = month;
		r.birthday[2] = year;

		// получаем знак зодиакая
		r.zodiak = get_zodiak_by_data(day, month);
	}

	// если мы вводим нового человека, то выводим зодиак
	if (write_surname && write_name && write_date) {
		cout << "Зодиак: " << r.zodiak << endl;
	}
}

int main(int argc, char** argv) {
	  system("chcp 65001");
	(LC_CTYPE, "Russian");
	// SetConsoleCP(1251);
	// SetConsoleOutputCP(1251);

	List* head = NULL;
	List* cur = NULL;
	int n = -1;
	ZNAK r;

	// Меню пользователя
	while (n != 0) {
		draw_line(40);
		cout <<
			"1 - Вывод списка" << endl <<
			"2 - Добавить в конец" << endl <<
			"3 - Добавить в начало" << endl <<
			"4 - Поиск по имени" << endl <<
			"5 - Поиск по фамилии" << endl <<
			"6 - Поиск по дате рождения" << endl <<
			"7 - Поиск по задиаку" << endl <<
			"8 - Удаление" << endl <<
			"9 - Редактировать" << endl <<
			"10 - Сохранить в файл" << endl <<
			"11 - Считать файл" << endl <<
			"0 - Выход" << endl;

		while (true) {
			n = read_int(" >> ");
			if (n < 0 || n > 11) {
				cout << "Такого пункта в меню нет." << endl;
			} else break;
		}

		draw_line(40);

		switch (n) {

		// вывод списка
		case 1: {
			if (head)
				PrintList(head, cout);
			else
				cout << "Нет данных!" << endl;
			break;
		}

		// добавить в конец
		case 2: {
			inputData(r);
			AddElem(&head, &cur, r);
			break;
		}

		// добавить в начало
		case 3: {
			inputData(r);
			AddFirstElem(&head, r);
			break;
		}

		// поиск по имени
		case 4: {
			if (!head) {
				cout << "Нет данных!" << endl;
				break;
			}
			inputData(r, true, false, false);
			FindElem(head, r, true, false, false, false);

			break;
		}

		// поиск по фамилии
		case 5: {
			if (!head) {
				cout << "Нет данных!" << endl;
				break;
			}
			inputData(r, false, true, false);
			FindElem(head, r, false, true, false, false);

			break;
		}

		// поиск по дате рождения
		case 6: {
			if (!head) {
				cout << "Нет данных!" << endl;
				break;
			}
			inputData(r, false, false, true);
			FindElem(head, r, false, false, false, true);

			break;
		}

		// поиск по знаку зодиака
		case 7: {
			if (!head) {
				cout << "Нет данных!" << endl;
				break;
			}
			// inputData(r, false, false, true);
			cin.ignore();
			r.zodiak = read_string("Введите название зодиака: ");
			FindElem(head, r, false, false, true, false);

			break;
		}

		// удалние
		case 8: {
			if (!head) {
				cout << "Нет данных!" << endl;
				break;
			}
			int id;
			int size = GetSizeList(head);
			id = read_int("ID удаляемого элемента: ");
			if (id < 0 || id > size) {
				cout << "Такого id не существует.";
				break;
			}
			List* ptr = GetById(head, id);
			DelElem(&head, ptr);
			cout << "Запись удалена!" << endl;
			break;
		}

		// редактирование
		case 9: {
			if (!head) {
				cout << "Нет данных!" << endl;
				break;
			}
			int id;
			int size = GetSizeList(head);
			id = read_int("ID удаляемого элемента: ");
			if (id < 0 || id > size) {
				cout << "Такого id не существует.";
				break;
			}
			List* ptr = GetById(head, id);
			ZNAK r2;
			inputData(r2);
			UpdateElem(&ptr, r2);
			cout << "Запись отредактирована!" << endl;
			break;
		}

		// запись в файл
		case 10: {
			cin.ignore();
			string fname = read_string("Введите имя файла для сохранения списка: ");
			ofstream file;
			file.open(fname);
			if (!file.is_open()) {
				cout << "Невозможно открыть файл для сохранения списка!";
			} else {
				if (head) {
					PrintList(head, file, true);
					cout << "Список сохранен в файл!" << endl;
				} else
					file << "Нет данных!" << endl;
			}
			file.close();
			break;
		}

		// чтение из файла
		case 11: {
			cin.ignore();
			string fname = read_string("Введите имя файла для чтения списка: ");
			ifstream file;

			// буферные переменные для ввода с файла
			string name;
			string surname;
			string zodiak;
			string day;
			string month;
			string year;

			file.open(fname);
			if (!file.is_open()) {
				cout << "Невозможно открыть файл для чтения списка!" << endl;
			} else {
				head = NULL;
				while(!file.eof()) {
					try {
						// очищаем буферные переменные
						name = "";
						surname = "";
						zodiak = "";
						day = "";
						month = "";
						year = "";

						// читаем с файла
						file >> name >> surname >> zodiak >> day >> month >> year;

						// проверяем на корректность чтения с файла
						if (check_str_to_int(day) && check_str_to_int(month) && check_str_to_int(year)) {
							r.name = name;
							r.surname = surname;
							r.zodiak = zodiak;
							r.birthday[0] = stoi(day);
							r.birthday[1] = stoi(month);
							r.birthday[2] = stoi(year);

							// добавляем элемент
							AddElem(&head, &cur, r);
						} else {
							cout << "Ошибка чтения файла." << endl;
						}
					} catch (...) {
						cout << "Ошибка чтения файла." << endl;
					}

				}
			}
			file.close();
			break;
		}
	}
}
	Free(&head);

	system("pause");
	return 0;
}
