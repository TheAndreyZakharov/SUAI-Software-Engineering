
#include <iostream>
using namespace std;

namespace global {
extern int count_count_subordinates;
}

// Директор
class Director: public Employee {
public:
    Director(char* full_name, int Year_of_admission, double Salary, int Amoun_departments, int Allowance);
    
    void info();
    double calculate_money();
    int get_count_subordinates();
    
protected:
    int amoun_departments; // количество отделов
    int allowance; // надбавка
};

Director::Director(char* full_name, int Year_of_admission, double Salary, int Amoun_departments, int Allowance) :Employee(full_name, Year_of_admission, Salary) {
    amoun_departments = Amoun_departments;
    allowance = Allowance;
}

void Director::info() {
    cout << "Директор" << endl;
    show_info();
    cout << "Количество отделов: " << amoun_departments << endl;
    cout << "Надбавка: " << allowance << " руб"<< endl;
    printf("Саммарное зп: %.2lf руб\n", calculate_money());
    cout << "Количество подчинённых: " << get_count_subordinates() << endl;
}

int Director::get_count_subordinates() {
    return global::count_count_subordinates;
}

double Director::calculate_money() {
    return calculate_salary();
}
