
#include <iostream>
using namespace std;

class MyException : public runtime_error {
    int DataState;
public:
    MyException(char*, int);
    // ~MyException() {}
    int GetData();
};

MyException::MyException(char* msg, int DataState):runtime_error(msg) {
    this->DataState = DataState;
}

int MyException::GetData() { return DataState; }

void exception_func(int a) {
    if (a==0) {
        throw MyException((char*)"Вызвано исключение из класса!",a);
        
        exit(EXIT_FAILURE);
        abort();
    }
}
