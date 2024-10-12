
#include <iostream>
using namespace std;

#define rand_min -10
#define rand_max 10

class Array {
public:
    Array(int, bool, bool);
    ~Array();
    
    int* sort_arr();
    int* generator();
    void add(int);
    int pop(int);
    void draw(const char* promt);
    
    int find_el(int);
    int dif_els();
private:
    int* arr;
    
    int size;
    bool auto_sort;
    bool random;
    
};

// конструктор
Array::Array(int Size, bool Auto_sort = true, bool Random = true) {
    size = Size;
    auto_sort = Auto_sort;
    random = Random;
    
    arr = (int*)malloc(size * sizeof(int));
    if (random) {
        generator();
    } else {
        for (int i = 0; i < size; i++) {
            cout << "Array[" << i << "] = ";
            arr[i] = read_value("", false, false, false);
        }
    }
    
    draw("Изначальный массив: ");
    
    if (auto_sort) sort_arr();
}

// деструктор
Array::~Array() {
    free(arr);
}

// вывод массива
void Array::draw(const char* promt = "") {
    cout << promt;
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
}

// добавление элемента в массив
void Array::add(int x) {
    arr = (int*)realloc(arr, ++size * sizeof(int));
    
    arr[size - 1] = x;
    
    if (auto_sort) sort_arr();
}

int Array::find_el(int x) {
    // for (int i = 0; i < size; i++) {
    //   if (arr[i] == x) return i;
    // }
    // return -1;
    if (x > 0 && x < size)
        return arr[x];
    return 0;
}

int Array::dif_els(){
    int count = 1;
    int tmp = 0;
    for (int j = 1; j < size; j++) {
        for (int k = 0; k < j; k++) {
            if (arr[j] != arr[k]) {
                tmp = 1;
            } else {
                tmp = 0;
                break;
            }
            
        }
        count += tmp;
    }
    return count;
}

// удаление элемента в массиве
int Array::pop(int x) {
    
    int returned = arr[x];
    int* old_arr = (int*)malloc(size * sizeof(int));
    old_arr = arr;
    arr = (int*)malloc((size - 1) * sizeof(int));
    
    int i, j = 0;
    for (i = 0; i < size; i++) {
        if (i != x) arr[j++] = old_arr[i];
    }
    
    size--;
    free(old_arr);
    
    if (auto_sort) sort_arr();
    
    return returned;
}

// заполнение массива случайными числами
int* Array::generator() {
    for (int i = 0; i < size; i++) {
        arr[i] = random_int(rand_min, rand_max);
    }
    return arr;
}

// сортировка Простым извлечением
int* Array::sort_arr() {
    int i,y;
    for(i=size-1; i>0; i--)
    {
        int max=0;
        for (int y=1; y<=i; y++)
        {
            if(arr[y]>arr[max]) max=y;
        }
        int temp = arr[i];
        arr[i] = arr[max];
        arr[max] = temp;
    }
    return arr;
}
