/*
 4 вариант
 
 Стек – динамический; очередь – динамический
 1 Задание
 
 Генератор -> Очередь x3 -> Процессор <-> Стек
 
 */

#define AUTO true

#include <iostream>
using namespace std;

#include <cmath>
#include <time.h>
#include <iomanip>

#include "structs.h"
#include "generator.h"
#include "processor.h"

// количемтво генерируемых задач
#define count_generator_tasks 20

int main() {
    // смена кодировки
    system("chcp 65001");
    
    srand(time(NULL));
    
    /* Стек - последный вошёл, первый вышел */
    MYList *stack = new MYList(-1);
    
    /* Очередь - первый вошёл, первый вышел */
    MYList *queue1 = new MYList(-1);
    MYList *queue2 = new MYList(-1);
    MYList *queue3 = new MYList(-1);
    
    /* Генератор */
    Generator *generator = new Generator(count_generator_tasks, AUTO);
    
    /* Процессоры */
    Processors processors(stack, queue1, queue2, queue3, generator);
    processors.loop();
    
    delete stack;
    delete queue1;
    delete queue2;
    delete queue3;
    delete generator;
    
    return 0;
}
