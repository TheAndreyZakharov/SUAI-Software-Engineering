#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;


// рисует линию в терминале
void draw_line(int size = 20) {
  for (int i = 0; i < size; i++)
    cout << '-';
  cout << endl;
}

// генерирует случайное число в диапазоне от A до B
int random_int(int a, int b) {
  return a + (rand() % ( b - a + 1 ) );
}

// Ввод вещественного числа с проверкой
double read_double(){
    double x;
  while ( (scanf("%lf",&x) ) != 1 ) {
    printf("Неверное введенное значение, попробуйте еще: ");
    while(getchar() != '\n');
  }
  return x;
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
