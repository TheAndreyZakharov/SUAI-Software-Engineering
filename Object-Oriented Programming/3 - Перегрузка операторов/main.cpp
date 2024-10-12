#include <iostream>
#include <string>
using namespace std;

class Complex {
private:
    double r, im; //Реальная и воображаемая часть комплексного числа
    
public:
    Complex();
    Complex(double, double);
    ~Complex();
    
    double get_real(); //получить реальную часть
    double get_imaginary(); //получить вообр часть
    
    Complex operator + (const Complex& z);
    Complex operator - (const Complex& z);
    friend bool operator == (Complex& z1, Complex& z2);
    friend bool operator != (Complex& z1, Complex& z2);
    
    string complex_to_str(); //перевести в форму x + yi
    void str_to_complex(string z); // создать из строки новый класс где r = x, im = y
};

Complex::Complex() {
    r = 0;
    im = 0;
}

Complex::Complex(double x, double y) {
    r = x;
    im = y;
}

Complex::~Complex() {
    cout << "Уничтожен" << endl;
}

double Complex::get_real() {
    return r;
}

double Complex::get_imaginary() {
    return im;
}

Complex Complex::operator + (const Complex& z) {
    Complex new_z;
    new_z.r = r + z.r;
    new_z.im = im + z.im;
    return new_z;
}

Complex Complex::operator - (const Complex& z) {
    Complex new_z;
    new_z.r = r - z.r;
    new_z.im = im - z.im;
    return new_z;
}

bool operator == (Complex& z1, Complex& z2) {
    return ((z1.get_real() == z2.get_real()) && (z1.get_imaginary() == z2.get_imaginary()));
}

bool operator != (Complex& z1, Complex& z2) {
    return ((z1.get_real() != z2.get_real()) && (z1.get_imaginary() != z2.get_imaginary()));
}

string Complex::complex_to_str() {
    string z = to_string(r) + " + " + to_string(im) + "i";
    return z;
}

void Complex::str_to_complex(string z) {
    string x = "";
    int i = 0;
    while (z[i] != ' ') {
        x += z[i];
        i++;
    }
    r = stod(x);
    i += 3;
    x = "";
    while (z[i] != 'i') {
        x += z[i];
        i++;
    }
    im = stod(x);
}

int main() {
    setlocale(LC_ALL, "ru");
    Complex z1(5, 8);
    Complex z2(12, 10);
    cout << "Первое число z1 = " + z1.complex_to_str() << endl;
    cout << "Второе число z1 = " + z2.complex_to_str() << endl;
    Complex z3 = z1 + z2;
    cout << "При сложении получено число " + z3.complex_to_str() << endl;
    Complex z4 = z2 - z1;
    cout << "При вычитании получено число " + z4.complex_to_str() << endl;
    if (z1 == z2) cout << "z1 и z2 равны" << endl;
    if (z1 != z2) cout << "z1 и z2 не равны" << endl;
    string z;
    cout << "Введите комплексное число в формате x + yi" << endl;
    getline(cin, z);
    z1.str_to_complex(z);
    cout << "Теперь z1 = " + z1.complex_to_str() << endl;
}
