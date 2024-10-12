#include <iostream>
#include <cmath>

using namespace std;

void draw_float_array(double *arr, int size) {
  for (int i = 0; i < size; i++)
    cout << arr[i] << "\t";
  cout << endl;
}

void draw_int_array(int *arr, int size, const char *tab = "\t") {
  for (int i = 0; i < size; i++)
    cout << arr[i] << tab;
  cout << endl;
}

void draw_float_double_array(double **arr, int size_x, int size_y) {
  for (int y = 0; y < size_y; y++) {
    for (int x = 0; x < size_x; x++) {
      cout << arr[y][x] << "\t";
    }
    cout << endl;
  }
}

double **read_double_arr(double **arr, int size_x, int size_y, const char *promt = "", bool random = false) {
  int x, y;

  for (y = 0; y < size_y; y++)
    for (x = 0; x < size_x; x++) {
      if (random) {
        arr[y][x] = random_int(-10, 10);
      } else {
        cout << promt << "[" << y << "][" << x << "] = ";
        arr[y][x] = read_value("", true, true, false);
      }
    }

    return arr;
}

double **create_arr(int size_x, int size_y) {
  double **arr = (double**)malloc(size_y * sizeof(double*));
  for(int i = 0; i < size_y; i++) {
      arr[i] = (double*)malloc(size_x * sizeof(double));
  }

  return arr;
}
