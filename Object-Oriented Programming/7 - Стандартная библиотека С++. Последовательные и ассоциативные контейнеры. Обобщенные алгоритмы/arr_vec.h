

#include <iostream>
using namespace std;

#include <algorithm>

#include <iomanip>
#include <vector>

#define rand_min -50 // m1
#define rand_max 50  // m2
//#define separator_show " " //

// рисует линию в терминале
void draw_line(int size = 20) {
    for (int i = 0; i < size; i++)
        cout << '-';
    cout << endl;
}

// генерирует случайное число в диапазоне от A до B
int random_int(int a, int b) {
    return a + (rand() % ( b - a + 1 ) );
}

// класс реализующий работу с вектором
class Arr_vec {
public:
    Arr_vec(int);
    ~Arr_vec();
    
    void generator(int);
    void show(const char* separator);
    void chenage_on_zero();
    void devide_all();
    bool swap_els(int);
    
private:
    vector <int> my_vector;
};

// конструктор
Arr_vec::Arr_vec(int Size) {
    // my_vector.reserve(Size);
    generator(Size);
}

// деструктор
Arr_vec::~Arr_vec() {
    
}

// метод заполняющий вектор случайными числами
void Arr_vec::generator(int Size) {
    for (int i = 0; i < Size; i++) {
        my_vector.push_back(random_int(rand_min, rand_max));
    }
}

// вывод массива на экран
void Arr_vec::show(const char* separator = " ") {
    for (int i = 0; i < my_vector.size(); i++) {
        cout << setw(4) << my_vector.at(i) << separator;
    }
    cout << endl;
}

// замена эелементов массива (всё что меньше 10 заменить на 0)
void Arr_vec::chenage_on_zero() {
    // for (int i = 0; i < my_vector.size(); i++) {
    //   if (my_vector.at(i) < 10)
    //     my_vector.at(i) = 0;
    // }
    replace_if(my_vector.begin(), my_vector.end(), [](int i) {return i < 10;}, 0);
}

// поделить все элементы массива на 2
int xform(int i) {
    return i / 2;
}

void Arr_vec::devide_all() {
    transform(my_vector.begin() , my_vector.end(), my_vector.begin(), xform);
}

// зеркально обменять 2 первых элемента массива с 2 последними
bool Arr_vec::swap_els(int count = 2) {
    if (count * 2 > my_vector.size())
        return false;
    
    for (int i = 0; i < count; i++) {
        swap(my_vector.at(i), my_vector.at(my_vector.size() - i - 1));
    }
    
    return true;
}
