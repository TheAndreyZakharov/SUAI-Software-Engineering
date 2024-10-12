
#include <iostream>
using namespace std;

#include <iomanip>

#define rand_min -10
#define rand_max 10

/*----------------------------------------------------------------------------*/

// генерирует случайное число в диапазоне от A до B
int random_int(int a, int b) {
    return a + (rand() % ( b - a + 1 ) );
}

// Ввод целого числа с проверкой
int read_int(){
    int x;
    while ( (scanf("%d",&x) ) != 1 ) {
        printf("Неверное введенное значение, попробуйте еще: ");
        while(getchar() != '\n');
    }
    return x;
}

/*----------------------------------------------------------------------------*/


class Array {
public:
    Array(int);
    ~Array();
    
    void generate(bool);
    void show(const char* separator);
    int* get_arr();
    int get_min();
    int get_sum();
    void my_sort();
private:
    int size;
    int *arr;
};

// конструктор
Array::Array(int Size) {
    size = Size;
    arr = (int*) malloc(size * sizeof(int));
    generate(false);
}

// деструктор
Array::~Array() {
    free(arr);
}

// заполенение массива
void Array::generate(bool random = false) {
    if (random) {
        for (int i = 0; i < size; i++) {
            arr[i] = random_int(rand_min, rand_max);
        }
    } else {
        for (int i = 0; i < size; i++) {
            cout << "Array[" << i << "] = ";
            arr[i] = read_int();
            
            try {
                exception_func(arr[i]);
            }
            catch (MyException &ex) {
                
                cout << "Число записалось в массив! " << ex.what() <<endl;
                cout << "Число, из-за которого произошла ошибка = " << ex.GetData() <<endl;
            }
            
        }
    }
}

// вывод массива на экран
void Array::show(const char* separator = " ") {
    for (int i = 0; i < size; i++) {
        cout << setw(4) << arr[i] << separator;
    }
    cout << endl;
}

// возврат массива
int* Array::get_arr() {
    return arr;
}

// нахождение минимального элемента массива
int Array::get_min() {
    int min_id = 0;
    
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[min_id])
            min_id = i;
    }
    
    return min_id;
}

// сумма элементов массива, расположенных между первым и последним положительными элементами
int Array::get_sum() {
    bool ok = false;
    for (int i = 0; i < size; i++) {
        if (arr[i] > 0)
            ok = true;
    }
    
    if (!ok)
        throw runtime_error ("В массиве нет положительных элементов.");
    
    int sum = 0;
    
    int perv_id = -1;
    int posl_id = -1;
    
    int i;
    for (i = 0; i < size; i++)
        if (arr[i] > 0) {
            perv_id = i;
            break;
        }
    
    for (i = size - 1; i > -1; i--)
        if (arr[i] > 0) {
            posl_id = i;
            break;
        }
    
    if (perv_id == posl_id)
        throw runtime_error ("В массиве только 1 положительный элемент.");
    
    for (i = perv_id + 1; i < posl_id; i++)
        sum += arr[i];
    
    return sum;
}

// сортиовка (сначала 0)
void Array::my_sort() {
    int* new_arr = (int*) malloc(size * sizeof(int));
    int j = 0;
    
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0)
            new_arr[j++] = arr[i];
    }
    
    for (int i = 0; i < size; i++) {
        if (arr[i] != 0)
            new_arr[j++] = arr[i];
    }
    
    arr = new_arr;
}
