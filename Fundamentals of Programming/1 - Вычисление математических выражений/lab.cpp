#include <iostream> //ввод, вывод
#include <cmath> // математические функции и константы
#include <iomanip> //число знаков после точки
using namespace std;

const double PI = 3.141592654;

// Функция для проверки ввода
int is_num() {
    double a;
    while (!(cin >> a) || (cin.peek() != '\n')) {
        cin.clear();
        while (cin.get() != '\n'); {
            cout << "Неверное введенное значение, попробуйте еще: ";
        }
        return a;
    }
}

double z_1(double m) {
    double z1 = (sqrt(pow(3*m + 2, 2) - 24 * m)) / ((3 * sqrt(m)) - (2 / sqrt(m)));
    return z1
}

double z_2(double m) {
    double z2 = -sqrt(m);
    return z2;
}

// перевод в радианы
double grad_to_rad(double deg) {
    return (deg / (180 / PI));
}

// Функция округления
double rround(double r) {
    return r = round(r * pow(10, 9)) / pow(10, 9);
}

int main() {
    setlocale(LC_ALL, "Russian");

    // ввод угла в градусах
    cout << "Введите угол (в градусах): ";
    double a = is_num();
    
    // перевод градусов в радианы
    a = grad_to_rad(a);

    // первое выражение
    double z1 = z_1(a);
    cout << setprecision(9) << "Z1 = " << z1 << endl;

    // второе выражение
    double z2 = z_2(a);
    cout << setprecision(9) << "Z2 = " << z2 << endl;
    
    int r = pow(10, 9);
    if (rround(z1) == rround(z2)) {
        cout << "Ответы равны";
    }
    else {
        cout << "Ответы не равны";
    }
}
