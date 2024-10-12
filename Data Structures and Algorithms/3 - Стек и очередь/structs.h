
#include <iostream>
using namespace std;

// элемент стека или очереди
struct Task {
    unsigned int priority; // приоритет
    unsigned int taskTime; // момент поступления
    unsigned int durationTime; // длительность выполнения
};

// вывод элемента стека или очереди
void draw_task(Task task, int tick = 0) {
    if (task.durationTime != 0) {
        cout << " - ";
        cout << "Время поступления " << task.taskTime;
        cout << " Приоритет " << task.priority;
        cout << " Такты " << task.durationTime;
        if (tick != 0) cout << " (" << tick << ")";
        cout << endl;
    } else {
        cout << "Пусто" << endl;
    }
}

// вывод всего стека или очереди
void draw_stack(Task *stack, int size) {
    if (size > 0) {
        for (int i = 0; i < size; i++) {
            draw_task(stack[i]);
        }
    } else {
        cout << "Пусто" << endl;
    }
    
}

// класс реализующий Стек и Очередь
class MYList {
public:
    Task *tmp = nullptr;
    int count = 0;
    int max_count;
    
    MYList(int Max_count);
    ~MYList();
    bool append(int priority, int taskTime, int durationTime, bool end);
    Task pop(int id);
    Task get(int id);
    Task *get_all();
    int get_size();
    
};

// конструктор
MYList::MYList(int Max_count) {
    max_count = Max_count;
    count = 0;
    tmp = nullptr;
    
}

// деструктор
MYList::~MYList() {
    free(tmp);
}

// добавление элемента
bool MYList::append(int priority, int taskTime, int durationTime, bool end = false) {
    if ((max_count == -1) || (count < max_count)) {
        if (tmp != nullptr) {
            tmp = (Task*)realloc(tmp, (++count) * sizeof(Task));
        } else {
            tmp = (Task*)malloc(sizeof(Task));
            count = 1;
        }
        
        if (end) {
            tmp[count - 1].priority = priority;
            tmp[count - 1].taskTime = taskTime;
            tmp[count - 1].durationTime = durationTime;
            
        } else {
            Task *buf = (Task*)malloc((count) * sizeof(Task));
            
            buf[0].priority = priority;
            buf[0].taskTime = taskTime;
            buf[0].durationTime = durationTime;
            
            for (int i = 0; i < count - 1; i++) {
                buf[i + 1].priority = tmp[i].priority;
                buf[i + 1].taskTime = tmp[i].taskTime;
                buf[i + 1].durationTime = tmp[i].durationTime;
            }
            
            tmp = buf;
            
        }
        
        return true;
    } else return false;
    
}

// вырезание элемента с возвратом
Task MYList::pop(int id) {
    Task *buf = tmp;
    
    tmp = (Task*)malloc((count - 1) * sizeof(Task));
    
    int index = 0;
    for (int i = 0; i < count; i++) {
        if (i != id)
            tmp[index++] = buf[i];
    }
    
    --count;
    
    return buf[id];
    
}

// получить 1 элемент
Task MYList::get(int id) {
    return tmp[id];
}

// получить все элементы
Task *MYList::get_all() {
    return tmp;
}

// получить текущий размер
int MYList::get_size() {
    return count;
}
