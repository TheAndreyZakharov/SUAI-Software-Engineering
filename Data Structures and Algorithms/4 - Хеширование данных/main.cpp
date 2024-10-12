/*
 4 вариант
 
 Линейное опрабирование
 2500 сигментов
 ЦЦЦБЦЦ
 */

#include <iostream>
using namespace std;

#include <cmath>
#include <time.h>
#include <iomanip>

// функции для работы со строками
#include "simple_char.h"

// методы для хуширования
#include "hash.h"

// генерирует случайное число в диапазоне от A до B
int random_int(int a, int b) {
    return a + (rand() % ( b - a + 1 ) );
}

// (говно) Ввод вещественного числа с проверкой
double read_double(){
    double x;
    while ( (scanf("%lf",&x) ) != 1 ) {
        printf("Неверное введенное значение, попробуйте еще: ");
        while(getchar() != '\n');
    }
    fflush(stdin);
    return x;
}

int menu() {
    int id;
    while (true) {
        cout << endl;
        cout << "1) Сгенерировать ключ" << endl;
        cout << "2) Ввести ключ вручную" << endl;
        cout << "3) Сгенерировать список ключей" << endl;
        cout << "4) Вывести список ключей" << endl;
        cout << "5) Очистить список ключей" << endl;
        cout << "6) Экспортировать в файл" << endl;
        cout << "7) Поиск по номеру сегмента" << endl;
        cout << "8) Поиск по ключу" << endl;
        cout << "0) Выход" << endl;
        cout << " >>> ";
        id = read_double();
        if (id >= 0 && id <= 8) {
            return id;
            
        } else {
            cout << "Этого нет в меню" << endl;
            
        }
    }
    
}

int main() {
    // смена кодировки
    system("chcp 65001");
    
    srand(time(NULL));
    
    /*
     i (int) = число
     c (char) = буква
     */
    
    My_hash my_hash("iiicii", 6);
    
    int menu_i;
    while (true) {
        menu_i = menu();
        
        switch (menu_i) {
            case (0):
                return 0;
                break;
                
            case (1):
                my_hash.generate();
                break;
                
            case (2):
                my_hash.generate(false);
                break;
                
            case (3):
                int count;
                while (true) {
                    cout << "Количество ключей: ";
                    count = read_double();
                    if (count > 0) {
                        for (int i = 0; i < count; i++)
                            my_hash.generate();
                        break;
                    } else
                        cout << "Число должно быть больше 0." << endl;
                }
                break;
                
            case (4):
                my_hash.draw_hash_list();
                break;
                
            case (5):
                my_hash.clear_hash_list();
                break;
                
            case (7):{
                cout << "Номер сегмента: ";
                int id = read_double();
                my_hash.get_find_by_id(id);
                break;
            }
                
            case (8):{
                char* key = my_hash.read_key();
                my_hash.get_find_by_key(key);
                break;
            }
                
            case (6):
                int file_name_length;
                cout << "Название файла: ";
                char* file_name = get_string(&file_name_length);
                my_hash.export_to_file(file_name);
                break;
                
        }
        
    }
    
    cout << my_hash.generate() << endl;
    
    return 0;
}
