#include <iostream>
#include <cmath>
 
using namespace std;
 
double func(double x, double a, double b) {
   return log(x + a) + pow(x + b, 5);
}
 
double firstDerivative(double x, double a, double b) {
   double h = 0.01; // шаг производной
   return (func(x + h, a, b) - func(x - h, a, b)) / (2 * h);
}
 
double secondDerivative(double x, double a, double b) {
   double h = 0.01; // шаг производной
   return (func(x + h, a, b) - 2 * func(x, a, b) + func(x - h, a, b)) / (h * h);
}
 
double findRoot(double x0, double x1, double eps, double a, double b) {
   double xPrev = x0;
   double xCurrent = x1;
   
   while (fabs(xCurrent - xPrev) > eps) {
       xPrev = xCurrent;
       xCurrent = x0 + (x1 - x0) / (1 - func(x1, a, b) / func(x0, a, b));
       
       printf("\nx = %.5f  F(x) = %.5f\n" , xCurrent, func(xCurrent, a, b));
       
       if (func(x0, a, b) * func(xCurrent, a, b) < 0) {
           x1 = xCurrent;
       }
       else if (func(xCurrent, a, b) * func(x1, a, b) < 0) {
           x0 = xCurrent;
       }
       else
           return xCurrent;
   }
   
   return xCurrent;
}
 
bool isCorrectParam(double x0, double x1, double eps, double a, double b) {
   if ( func(x0, a, b) * func(x1, a, b) >= 0 )
       return false;
   
   bool isPositiveDx = firstDerivative(x0, a, b) > 0;
   double i = x0;
   
   while (i < x1) {
       if ( firstDerivative(i, a, b) < 0 && isPositiveDx )
           return false;
       else if ( firstDerivative(i, a, b) > 0 && !isPositiveDx)
           return false;
       i += 0.01;
   }
   
   isPositiveDx = secondDerivative(x0, a, b) > 0;
   i = x0;
   
   while (i < x1) {
       if ( secondDerivative(i, a, b) < 0 && isPositiveDx )
           return false;
       else if ( secondDerivative(i, a, b) > 0 && !isPositiveDx )
           return false;
       else if ( secondDerivative(i, a, b) == 0 )
           return false;
       i += 0.01;
   }
   return true;
}
 
int main() {
   double x0, x1;
   double a, b;
   double eps = 3 * pow(10, -5);
   bool global_break = false;
   int choice = 0;
   
   while (!global_break) {
       cout << "1 - использовать параметры по умолчанию\n2 - ввести параметры вручную\n0 - завершить выполнение программы\n";
       cout << "\nВаш выбор: ";
       cin >> choice;
       
       switch (choice){
           case 0:
               global_break = true;
               cout << "\nВыполнение программы завершено\n";
               break;
               
           case 1:
               x0 = 2.8; x1 = 3.5;
               a = 2.11; b = -4.03;
               eps = 3 * pow(10, -5);
               
               cout << "\nИспользуются параметры по умолчанию: \n";
               cout << "\nНачальное приближение [" << x0 << ", " << x1 << "]\n";
               cout << "a = " << a << "  b = " << b << "  eps = " << eps << endl;
               
               if (func(x0, a, b) * secondDerivative(x0, a, b) > 0) {
                   findRoot(x0, x1, eps, a, b);
               } else if (func(x1, a, b) * secondDerivative(x1, a, b) > 0) {
                   findRoot(x1, x0, eps, a, b);
               }
               
               global_break = true;
               break;
               
           case 2:
               cout << "\nНачало отрезка:\nx0 = ";
               cin >> x0;
               
               cout << "\nКонец отрезка:\nx1 = ";
               cin >> x1;
               
               cout << "\nВведите параметр a:\na = ";
               cin >> a;
               
               cout << "\nВведите параметр b:\nb = ";
               cin >> b;
               
               cout << "\nВведите необходимую точность:\neps = ";
               cin >> eps;
               
               if (isCorrectParam(x0, x1, eps, a, b)) {
                   if (func(x0, a, b) * secondDerivative(x0, a, b) > 0) {
                       findRoot(x0, x1, eps, a, b);
                   } else if (func(x1, a, b) * secondDerivative(x1, a, b) > 0) {
                       findRoot(x1, x0, eps, a, b);
                   }
                   cout << endl;
                   global_break = true;
                   
               } else {
                   cout << "\nВведены некорректные данные!\n\n";
               }
               break;
           
           default:
               cout << "\nТакого действия нет. Повторите ввод:\n\n";
               break;
       }
   }
   
   return 0;
}
