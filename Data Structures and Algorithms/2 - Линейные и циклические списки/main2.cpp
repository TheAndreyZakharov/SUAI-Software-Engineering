/*
 4 вариант (26 % 23) + 1
 
 
 */

#include <iostream>
using namespace std;

#include <cmath>
#include <time.h>
#include <iomanip>

#include "structs.h"

void draw_line(int size = 20) {
    for (int i = 0; i < size; i++)
        cout << '-';
    cout << endl;
}

// проверка ввода 
int read_int(const char* promt="") {
    int x;
    cout << promt;
    while ( (scanf("%d",&x) ) != 1 ) {
        printf("Неверное введенное значение, попробуйте еще: ");
        while(getchar() != '\n');
    }
    return x;
}


list *get_func(int n, list *tmp, const char *promt = "") {
    int a;
    for (int i = n - 1; i >= 0; i--) {
        cout << promt << "[" << i << "] = ";
        a = read_int("");
        if (a != 0)
            if (tmp == NULL) {
                tmp = create(i, a);
            } else {
                add_element_end(i, a, tmp);
            }
    }
    
    return tmp;
}

void draw_table(list *tmp) {
    // int length_A = get_length_list(list_a);
    // int length_B = get_length_list(list_b);
    
    int i = 0;
    
    cout << "| ID | X  | A  |\n";
    
    // for (int i = 0; i < ((length_A > length_B)? length_A: length_B); i++) {
    while (tmp != NULL) {
        cout << "| " << setw(3) << i;
        cout << "| " << setw(3) << tmp -> n;
        cout << "| " << setw(3) << tmp -> a;
        cout << "|" << endl;
        tmp = tmp -> next;
        i++;
    }
    
}

int menu() {
    while (true) {
        cout << "1) Добавить элемент в список Q" << endl;
        cout << "2) Удалить элемент из списока Q" << endl;
        cout << "3) Добавить элемент в список R" << endl;
        cout << "4) Удалить элемент из списка R" << endl << endl;
        cout << "0) Выход" << endl;
        int id = read_int(" >>> ");
        if (0 <= id < 5) {
            return id;
            
        } else {
            cout << "Этого нет в меню" << endl;
            
        }
    }
    
}

list *delete_element(list *tmp, int id) {
    int i = 0;
    int length = get_length_list(tmp) - 1;
    list *new_list = NULL;
    
    while (tmp != NULL) {
        if (id != i) {
            if (new_list == NULL) {
                new_list = create(tmp -> n, tmp -> a);
            } else {
                add_element_end(tmp -> n, tmp -> a, new_list);
            }
        }
        tmp = tmp -> next;
        i++;
    }
    return new_list;
}

list *append_element(list *tmp, int n, int a) {
    list *old = tmp;
    if (tmp == NULL) {
        tmp = create(n, a);
        return tmp;
    }
    
    add_element_end(n, a, old);
    return old;
}

int main() {
    // смена кодировки
    system("chcp 65001"); // setlocale(LC_ALL, "Russian");
    
    list *q_list = NULL;
    list *r_list = NULL;
    list *p_list = NULL;
    
    int menu_i;
    
    int id;
    int a;
    
    int x1 = 0;
    int x2 = 0;
    
    while (true) {
        draw_line();
        draw_func(q_list, "Q(x) = ");
        draw_func(r_list, "R(x) = ");
        p_list = merge_func(q_list, r_list);
        draw_func(p_list, "P(x) = ");
        
        menu_i = menu();
        switch (menu_i) {
            case (0):
                return 0;
                break;
                
            case (1):
                draw_table(q_list);
                //id = read_int("x: ");
                a = read_int("a: ");
                if (a != 0){
                    q_list = append_element(q_list, x1++, a);
                }
                break;
                
            case (2):
                draw_table(q_list);
                id = read_int("ID: ");
                q_list = delete_element(q_list, id);
                break;
                
            case (3):
                draw_table(r_list);
                //id = read_int("x: ");
                a = read_int("a: ");
                if (a != 0){
                    r_list = append_element(r_list, x2++, a);
                }
                
                break;
                
            case (4):
                draw_table(r_list);
                id = read_int("ID: ");
                r_list = delete_element(r_list, id);
                break;
        }
    }
    
    return 0;
}
