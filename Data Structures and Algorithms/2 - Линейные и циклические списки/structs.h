
#include <iostream>
using namespace std;

struct list {
    int n;
    int a;
    struct list *next = NULL;
    
};

list *create(int n, int a) {
    
    list *tmp = (list*)malloc(sizeof(list));
    
    tmp -> n = n;
    tmp -> a = a;
    
    tmp -> next = NULL;
    return tmp;
}

void add_element_end(int n, int a, list *head) {
    list *tmp = (list*)malloc(sizeof(list));
    tmp -> n = n;
    tmp -> a = a;
    list *p = head;
    while (p -> next != NULL)
        p = p -> next;
    p -> next = tmp;
    
}

int get_length_list(list *tmp) {
    int length = 0;
    while (tmp != NULL) {
        length++;
        tmp = tmp -> next;
    }
    return length;
}

void draw_list(list *number_list) {
    while (number_list != NULL){
        cout << number_list -> n << "|" << number_list -> a << endl;
        number_list = number_list -> next;
    }
}

void draw_func(list *tmp, const char *promt = "") {
    cout << promt;
    bool first = true;
    if (tmp == NULL) {
        cout << "NULL" << endl;
        return;
    }
    
    int i = get_length_list(tmp) - 1;
    
    while (tmp != NULL) {
        if (tmp -> a != 0) {
            if (!first)
                cout << " + ";
            else first = false;
            
            
            cout << tmp -> a;
            
            if (i != 0) cout << "x^" << i--;
            
        }
        
        tmp = tmp -> next;
    }
    cout << endl;
}

int get_size_list(list *tmp) {
    int size = 0;
    while (tmp != NULL) {
        size++;
        tmp = tmp -> next;
    }
    return size;
}

list *merge_func(list *a, list *b) {
    list *tmp = NULL;
    
    int size_a = get_size_list(a);
    int size_b = get_size_list(b);
    
    if (size_b > size_a) {
        list *buf = a;
        a = b;
        b = buf;
    }
    
    int n_a = get_size_list(a) - 1;
    int n_b = get_size_list(b) - 1;
    
    while (a != NULL) {
        if (b != NULL && ((n_b) == (n_a))) {
            
            if (tmp == NULL) {
                tmp = create(n_a, (a -> a) + (b -> a));
            } else {
                add_element_end(n_a, (a -> a) + (b -> a), tmp);
            }
            n_b--;
            b = b -> next;
            
        } else {
            
            if (tmp == NULL) {
                tmp = create(n_a, a -> a);
            } else {
                add_element_end(n_a, a -> a, tmp);
            }
        }
        
        
        n_a--;
        a = a -> next;
    }
    
    return tmp;
}
