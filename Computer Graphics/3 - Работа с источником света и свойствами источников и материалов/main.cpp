
/*
 
 Вывести сложный трехмерный объект, сохранить его в виде списка и размножить
 в виде нескольких копий различного масштаба на экране путем повторного
 вывода списка. Выводимые объекты располагаются над рельефом, задаваемым
 NURBS-поверхностью. Наложить текстуру на выводимые объекты, сцена должна
 быть освещена, необходимо предусмотреть возможность включения эффекта
 тумана (при помощи клавиатуры или мыши).
 
 */
#define _CRT_SECURE_NO_WARNINGS
#define GL_SILENCE_DEPRECATION

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GLUT/GLUT.h>

#include <iostream>
#include <cmath>



// функция для получения текстуры
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

#include "move.h" // функции для ПЕРЕДВИЖЕНИЯ
#include "models.h" // модели для списка
#include "draw.h" // функции для ПРОРИСОВКИ

#define TITLE "Nurbs, Textures && List"

#define W_WIDTH 1280
#define W_HEIGHT 720

#define FPS 60

namespace global {
float cam_xz_rotate = 0;
float cam_y_rotate = 0.2;
float cam_zoom = 14;
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
    glutMouseFunc(MouseWheel);
    
    // таймер
    glutTimerFunc(0, timer, 0);
    
    // чтоб окно не закрывалось
    glutMainLoop();
}
