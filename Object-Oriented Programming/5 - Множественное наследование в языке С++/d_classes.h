
#include <iostream>
using namespace std;

class D1: public B1, private B2 {
public:
    D1(int, int, int);
    ~D1();
    void show_D1();
    
public:
    int d1;
    
};

D1::D1(int x, int y, int z): B1(y), B2(z) {
    d1 = x;
    cout << "Конструктор с аргументами D1" << endl;
}

D1::~D1() {
    cout << "Деструктор D1" << endl;
}

void D1::show_D1() {
    cout << "D1 = " << d1 << endl;
    show_B1();
    show_B2();
    
}

/*----------------------------------------------------------------------------*/

class D2: private D1 {
public:
    D2(int, int, int, int);
    ~D2();
    void show_D2();
    
public:
    int d2;
    
};

D2::D2(int x, int y, int z, int i): D1(y, z, i) {
    d2 = x;
    cout << "Конструктор с аргументами D2" << endl;
}

D2::~D2() {
    cout << "Деструктор D2" << endl;
}

void D2::show_D2() {
    cout << "D2 = " << d2 << endl;
    show_D1();
    
}

/*----------------------------------------------------------------------------*/

class D3: public D2, private B3 {
public:
    D3(int, int, int, int, int, int);
    ~D3();
    void show_D3();
    
public:
    int d3;
    
};

D3::D3(int x, int y, int z, int i, int j, int k): D2(y, z, i, j), B3(k) {
    d3 = x;
    cout << "Конструктор с аргументами D3" << endl;
}

D3::~D3() {
    cout << "Деструктор D3" << endl;
}

void D3::show_D3() {
    cout << "D3 = " << d3 << endl;
    show_D2();
    show_B3();
    
}

/*----------------------------------------------------------------------------*/
