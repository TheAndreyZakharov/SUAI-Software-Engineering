#include <iostream>
#include <cmath>
 
using namespace std;
 
double func(int n, double a, double b) {
   double h = (b-a)/n; // шаг разбиения
   double sum = 0; // сумма площадей прямоугольников
   cout << "\nЗначения в частичных интервалах:\n";
   
   for (int i = 0; i < n; i++) {
       double x1 = a + i * h;
       double x2 = x1 + h;
       double xm = (x1 + x2) / 2;
       double val = tan(xm * xm + 0.5) / (1 + 2 * xm * xm) * h;
       sum += val;
       cout << val << endl;
   }
   return sum;
}
 
int main() {
   bool global_break = false;
   int choice = 0;
   
   while (!global_break) {
       cout << "1 - использовать интервал и кол-во разбиений по умолчанию\n2 - ввести интервал и кол-во разбиений вручную\n0 - завершить выполнение программы\n";
       cout << "\nВаш выбор: ";
       cin >> choice;
       
       switch (choice){
           case 0:
               global_break = true;
               cout << "\nВыполнение программы завершено\n";
               break;
               
           case 1: {
               int n = 6; // количество интервалов разбиения
               double a = 0.4, b = 0.9; // границы интегрирования
               double sq;
               
               cout << "\nИнтервал интегрирования: [" << a << "; " << b << "]\n";
               cout << "Кол-во интервалов разбиения: " << n << endl;
               
               sq = func(n, a, b);
               cout << "\nЗначение интеграла: " << sq << endl << endl;
               
               global_break = true;
               break;
           }
           case 2: {
               int n ; // количество интервалов разбиения
               double a, b; // границы интегрирования
               double sq;
               
               cout << "\nВведите интервал интегрирования:\n";
               cout << "а = "; cin >> a;
               cout << "b = "; cin >> b;
               
               cout << "\nВведиете кол-во интервалов разбиения: ";
               cin >> n;
               
               sq = func(n, a, b);
               cout << "\nЗначение интеграла: " << sq << endl << endl;
             
               global_break = true;
               break;
           }
           default:
               cout << "\nТакого действия нет. Повторите ввод:\n\n";
               break;
       }
   }
   return 0;
}
 
