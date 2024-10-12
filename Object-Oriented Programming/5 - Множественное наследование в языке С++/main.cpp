/*
 16 вариант
 
 */

#include <iostream>
using namespace std;

#include <cmath>

#include "b_classes.h"
#include "d_classes.h"

int main() {
    // смена кодировки
    system("chcp 65001"); // setlocale(LC_ALL, "Russian");
    
    D3 d3(10, 20, 30, 40, 50, 60);
    d3.show_D3();
    
    return 0;
}
