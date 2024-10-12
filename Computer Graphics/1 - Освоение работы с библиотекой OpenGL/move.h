/*
 Здесь реализуются функции для ПЕРЕДВИЖЕНИЯ
 */

#include <GL/freeglut.h>

namespace global {
extern float cam_xz_rotate;
extern float cam_y_rotate;
extern float cam_zoom;
extern bool light_flag;
extern bool fog_flag;
}

bool left = false;
bool right = false;
bool up = false;
bool down = false;

// отпущенные клавишы
void keyUp(unsigned char key, int xx, int yy) {
    switch (key) {
        case ('a'):
            left = false;
            break;
            
        case ('d'):
            right = false;
            break;
            
        case ('w'):
            up = false;
            break;
            
        case ('s'):
            down = false;
            break;
            
            // выход
        case 27:
            exit (0);
            break;
    }
}

// нажатые клавишы
void keyDown(unsigned char key, int xx, int yy) {
    switch (key) {
        case ('a'):
            left = true;
            break;
            
        case ('d'):
            right = true;
            break;
            
        case ('w'):
            up = true;
            break;
            
        case ('s'):
            down = true;
            break;
            
        case ('l'):
            global::light_flag = !global::light_flag;
            break;
            
        case ('f'):
            global::fog_flag = !global::fog_flag;
            break;
    }
}

float fraction = 0.05;
float cam_y_rotate_max = 1.5;
// функция для рассчётов передвижений
void move() {
    if (left) {
        global::cam_xz_rotate -= fraction;
    }
    
    if (right) {
        global::cam_xz_rotate += fraction;
    }
    
    if (up && (global::cam_y_rotate + fraction < cam_y_rotate_max)) {
        global::cam_y_rotate += fraction;
    }
    
    if (down && (global::cam_y_rotate - fraction > -cam_y_rotate_max)) {
        global::cam_y_rotate -= fraction;
    }
    
}

float fraction_zoom = 1.0;
// прокрутка колеса мыши
void MouseWheel(int button, int dir, int x, int y) {
    if (dir > 0) {
        global::cam_zoom -= fraction_zoom;
    } else {
        global::cam_zoom += fraction_zoom;
    }
}
