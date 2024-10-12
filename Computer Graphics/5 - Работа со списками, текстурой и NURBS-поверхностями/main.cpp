#include <iostream>
#include <cmath>

#include <GL/freeglut.h>

// функция для получения текстуры
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "move.h" // функции для ПЕРЕДВИЖЕНИЯ
#include "models.h" // модели для списка
#include "draw.h" // функции для ПРОРИСОВКИ

#define TITLE "Nurbs, Textures && List"

#define W_WIDTH 1280
#define W_HEIGHT 720

#define FPS 60

namespace global {
float cam_xz_rotate = 1.5;
float cam_y_rotate = 0.4;
float cam_zoom = 20;
bool light_flag = true;
bool fog_flag = true;
}

// замена while
void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, timer, 0);
}

// ну тут уже ОЧЕВИДНО
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(150, 50);
    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    glutCreateWindow(TITLE);
    
    glPointSize(5);
    
    init_surface();
    fog_on();
    generate_textures();
    generate_list();
    
    // передаём функции для прорисовки
    glutReshapeFunc(Reshape);
    glutDisplayFunc(Display);
    
    //
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    
    // передаём функции для определения нажатых клавиш
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutMouseWheelFunc(MouseWheel);
    
    // таймер
    glutTimerFunc(0, timer, 0);
    
    // чтоб окно не закрывалось
    glutMainLoop();
}
