
#include <iostream>
#include <ctime>
using namespace std;

namespace global {
extern int count_count_subordinates;
}

int get_now_year() {
    time_t now = time(0);
    
    tm *ltm = localtime(&now);
    return (1900 + ltm -> tm_year);
}

class Employee {
public:
    Employee(char* full_name, int Year_of_admission, double Salary);
    
    void show_info();
    double calculate_salary();
    int get_experience();
    
protected:
    char* full_name;       // ФИО
    int year_of_admission;  // Год поступления на работу
    double salary;          // Оклад
    
};

// конструктор
Employee::Employee(char* Full_name, int Year_of_admission, double Salary) {
    full_name = Full_name;
    year_of_admission = Year_of_admission;
    salary = Salary;
    
    //if (director) count_subordinates++;
}

// вывод информации
void Employee::show_info() {
    //cout << "ФИО: " << full_name << end;
    printf("ФИО: %s\n", full_name);
    cout << "Год поступления на работу: " << year_of_admission << endl;
    cout << "Оклад: " << salary << " руб" << endl;
    cout << "Стаж работы: " << get_experience() << " лет" << endl;
}

int Employee::get_experience() {
    return (get_now_year() - year_of_admission);
}

// рассчёт зарплаты
double Employee::calculate_salary() {
    return (get_experience() * 12) * salary;
}
