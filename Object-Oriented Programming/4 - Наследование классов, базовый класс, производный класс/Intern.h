
#include <iostream>
using namespace std;

// Стажер
class Intern: public Employee {
public:
    Intern(char* full_name, int Year_of_admission, double Salary, char* Job_title, int Duration, double Diligence_bonus);
    void info();
    double calculate_money();
    
protected:
    char* job_title; // Должность
    int duration; // Продолжительность испытательного строка
    double diligence_bonus; // Надбавка за прилежность
};

Intern::Intern(char* full_name, int Year_of_admission, double Salary, char* Job_title, int Duration, double Diligence_bonus) :Employee(full_name, Year_of_admission, Salary) {
    job_title = Job_title;
    duration = Duration;
    diligence_bonus = Diligence_bonus;
}

void Intern::info() {
    cout << "Стажер" << endl;
    show_info();
    printf("Должность: %s\n", job_title);
    cout << "Продолжительность испытательного строка: " << duration << " дней" << endl;
    cout << "Надбавка за прилежность: " << diligence_bonus << " руб" << endl;
    printf("Саммарное зп: %.2lf руб\n", calculate_money());
}

double Intern::calculate_money() {
    return calculate_salary() + diligence_bonus;
}
