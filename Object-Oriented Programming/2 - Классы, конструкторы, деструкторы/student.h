
#include <iostream>
using namespace std;

#include <time.h>
#include <string.h>

class Student {
public:
    Student(); // конструктор по умолчанию
    Student(string Name, string Surname, int Year); // конструктор с аргуметами
    Student(const Student & ref_Student); // конструктор копирования
    ~Student();
    
    void getFullName();
    void getCourse();
    
private:
    string name;
    string surname;
    int year;
};

// конструктор по умолчанию
Student::Student() {
    name = "Иван";
    surname = "Иванов";
    year = 2007;
}

// конструктор с аргуметами
Student::Student(string Name, string Surname, int Year) {
    name = Name;
    surname = Surname;
    year = Year;
}

// конструктор копирования
Student::Student(const Student & ref_Student) {
    name  = ref_Student.name;
    surname  = ref_Student.surname;
    year  = ref_Student.year;
    cout << "Класс скопирован." << endl;
}

// деструктор
Student::~Student() {
    cout << "Стработал деструктор" << endl;
}

void Student::getFullName() {
    cout << "ФИО студента: " << name << " " << surname << endl;
}

// вывод времени
void Student::getCourse() {
    const time_t timer = time(NULL);
    struct tm *saved_time = localtime(&timer);
    
    cout << "Текущий курс студента: " << (1900 + saved_time -> tm_year) - year << endl;
    
}
