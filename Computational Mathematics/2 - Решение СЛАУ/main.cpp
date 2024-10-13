 
#include <iostream>
 
using namespace std;
 
// Вывод системы уравнений
void sysout(double a[], double* b, size_t n) {
   cout << endl;
   
   for (int i = 0; i < n; i++) {
       for (int j = 0; j < n; j++) {
           cout << a[i * n + j] << " * x" << j;
           if (j < n - 1)
           cout << " + ";
       }
       cout << " = " << b[i] << endl;
   }
   return;
}
 
bool gauss(double a[], double *y, size_t n) {
   double *x, max;
   int k, index;
   const double eps = 0.00001;  // точность
   x = new double[n];
   k = 0;
   
   while (k < n) {
     // Поиск строки с максимальным a[i][k]
     max = abs(a[k * n + k]);
     index = k;
       
     for (int i = k + 1; i < n; i++) {
         if (abs(a[i * n + k]) > max) {
             max = abs(a[i * n + k]);
             index = i;
         }
     }
     
       // Перестановка строк
       if (max < eps) {
         // нет ненулевых диагональных элементов
         cout << "\nРешение получить невозможно из-за нулевого столбца ";
         cout << index << " матрицы A" << endl;
         return false;
       }
     
       for (int j = 0; j < n; j++) {
           double temp = a[k * n + j];
           a[k * n + j] = a[index * n + j];
           a[index * n + j] = temp;
       }
     
       double temp = y[k];
       y[k] = y[index];
       y[index] = temp;
     
       // Нормализация уравнений
       for (int i = k; i < n; i++) {
           double temp = a[i * n + k];
       
           if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
       
           for (int j = 0; j < n; j++)
           a[i * n + j] = a[i * n + j] / temp;
       
           y[i] = y[i] / temp;
       
           if (i == k)  continue; // уравнение не вычитать само из себя
       
           for (int j = 0; j < n; j++)
               a[i * n + j] = a[i * n + j] - a[k * n + j];
       
           y[i] = y[i] - y[k];
       }
       k++;
   }
   
 // обратная подстановка
   for (k = n - 1; k >= 0; k--) {
       x[k] = y[k];
     
       for (int i = 0; i < k; i++)
           y[i] = y[i] - a[i * n + k] * x[k];
   }
   
   for (int i = 0; i < n; i++)
       cout << "x[" << i << "] = " << x[i] << endl;
   
   cout << endl;
   
   return true;
}
 
int main() {
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
               
           case 1: {
               double B[4] = {3, 8, 1, 7};
               
               double A[4][4] = {{1, 4, 2, 5},
                                 {4, 4, 5, 3},
                                 {1, 2, 6, 8},
                                 {3, 7, 3, 2}};
               
               sysout(&A[0][0], B, 4);
               if ( ! gauss(&A[0][0], B, 4) ) {
                   cout << "\nПовторите ввод:\n";
                   break;
               }
               
               global_break = true;
               break;
           }
           case 2:
               double **A, *B;
               int n;
               cout << "\nВведите количество уравнений: ";
               cin >> n;
               cout << endl;
               
               A = new double *[n];
               B = new double [n];
               
               for (int i = 0; i < n; i++) {
                   A[i] = new double[n];
                   for (int j = 0; j < n; j++) {
                       cout << "A[" << i << "][" << j << "] = ";
                       cin >> A[i][j];
                   }
               }
               cout << endl;
               
               for (int i = 0; i < n; i++) {
                   cout << "B[" << i << "] = ";
                   cin >> B[i];
               }
               
               sysout(&A[0][0], B, n);
               
               if ( ! gauss(&A[0][0], B, 4) ) {
                   cout << "\nПовторите ввод:\n";
                   break;
               }
               
               global_break = true;
               break;
               
           default:
               cout << "\nТакого действия нет. Повторите ввод:\n\n";
               break;
       }
   }
   return 0;
}
 
