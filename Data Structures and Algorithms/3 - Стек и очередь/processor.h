
#include <iostream>
//#include <conio.h>
using namespace std;

// рисует линию в терминале
void draw_line(int size = 20) {
    for (int i = 0; i < size; i++)
        cout << '-';
    cout << endl;
}

// класс реализующий работу процессороа и его логику
class Processors {
public:
    int tick_num = 0;
    
    Task buf = {0, 0, 0};
    int durationTime = 0;
    // bool run_processor = false;
    bool last_sended = false;
    
    MYList *stack;
    
    MYList *queue1;
    MYList *queue2;
    MYList *queue3;
    
    Generator *generator;
    
    bool run = true;
    
    Processors(MYList *stack1, MYList* _queue1, MYList* _queue2, MYList* _queue3, Generator* generator1);
    void tick();
    void loop();
};

// конструктор
Processors::Processors(MYList *stack1, MYList* _queue1, MYList* _queue2, MYList* _queue3, Generator* generator1) {
    stack = stack1;
    queue1 = _queue1;
    queue2 = _queue2;
    queue3 = _queue3;
    generator = generator1;
    
    Task buf;
    int i;
    
    int count_generator_task_to = generator -> get_size() / 3;
    
    for (i = 0; i < count_generator_task_to; i++) {
        buf = generator -> get();
        queue1 -> append(
                         buf.priority,
                         buf.taskTime,
                         buf.durationTime
                         );
    }
    
    for (i = 0; i < count_generator_task_to; i++) {
        buf = generator -> get();
        queue2 -> append(
                         buf.priority,
                         buf.taskTime,
                         buf.durationTime
                         );
    }
    
    int generator_remainder = generator -> get_size();
    for (i = 0; i < generator_remainder; i++) {
        buf = generator -> get();
        queue3 -> append(
                         buf.priority,
                         buf.taskTime,
                         buf.durationTime
                         );
    }
    
    run = true;
}

// цикл процессора
void Processors::loop() {
    char c;
    while (run) {
        draw_line();
        tick();
        
        cout << "Процессор: ";
        draw_task(buf, durationTime);
        
        cout << "Генератор:" << endl;
        draw_stack(generator -> list -> get_all(), generator -> get_size());
        
        cout << "Стек:" << endl;
        draw_stack(stack -> get_all(), stack -> get_size());
        
        cout << "Очередь #1:" << endl;
        draw_stack(queue1 -> get_all(), queue1 -> get_size());
        cout << "Очередь #2:" << endl;
        draw_stack(queue2 -> get_all(), queue2 -> get_size());
        cout << "Очередь #3:" << endl;
        draw_stack(queue3 -> get_all(), queue3 -> get_size());
        
        // 13 Enter
        // 27 escape
        // 8 backspace
        // 32 space
        c = getchar(); //getch();
        if (c == 8) run = false;
        
        if (!run) break;
    }
}

// итерция процессора
void Processors::tick() {
    tick_num++;
    cout << tick_num << " такт" << endl;
    
    // если очереди пусты, то берём задачи из стека
    int queue_summary_size = queue1 -> get_size() + queue2 -> get_size() + queue3 -> get_size();
    if (queue_summary_size <= 0 && durationTime <= 0) {
        if (stack -> get_size() > 0) {
            buf = stack -> pop((stack -> get_size()) - 1);
            durationTime = buf.durationTime;
            return;
        } else {
            buf = {0, 0, 0};
            
        }
    }
    
    // если процессор пуст, то берём новую задачу из очередей
    if (queue_summary_size > 0 && durationTime <= 0) {
        if (queue1 -> get_size() > 0) {
            buf = queue1 -> pop(0);
        } else if (queue2 -> get_size() > 0) {
            buf = queue2 -> pop(0);
        } else if (queue3 -> get_size() > 0) {
            buf = queue3 -> pop(0);
        }
        durationTime = buf.durationTime;
        return;
    }
    
    Task buf_priority;
    bool priority = false;
    
    // проверка на преоритет задачи в стеках
    if (queue1 -> get_size() > 0 && queue1 -> get(0).priority > buf.priority) {
        buf_priority = queue1 -> pop(0);
        priority = true;
    } else if (queue2 -> get_size() > 0 && queue2 -> get(0).priority > buf.priority) {
        priority = true;
        buf_priority = queue2 -> pop(0);
    } else if (queue3 -> get_size() > 0 && queue3 -> get(0).priority > buf.priority) {
        priority = true;
        buf_priority = queue3 -> pop(0);
    }
    
    // если имеется задача с более высоким приоритетом, то добавляем старую в стек и берём новую
    if (priority) {
        stack -> append(
                        buf.priority,
                        buf.taskTime,
                        buf.durationTime
                        );
        
        buf = buf_priority;
        durationTime = buf.durationTime;
        return;
    }
    
    
    //работа процессора
    if ((durationTime > 0)) {
        run = true;
        durationTime -= 1;
    } else {
        run = false;
    }
    
}
