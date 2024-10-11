#include <iostream>

using namespace std;

// функция рисующая полосу для разделения
void draw_line(int size) {
    for (int i = 0; i < size; i++)
        cout << '-';
    cout << endl;
}

int read_int() {
    int x;
    while ((scanf("%d", &x)) != 1) {
        printf("Неверное введенное значение, попробуйте еще: ");
        while (getchar() != '\n');
    }
    return x;
}
