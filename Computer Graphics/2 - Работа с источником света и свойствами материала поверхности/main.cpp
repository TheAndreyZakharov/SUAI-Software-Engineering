#define _CRT_SECURE_NO_WARNINGS
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <GLUT/glut.h>
#include <cstdio>
#include <math.h>


char title[] = "BOX 3D";

GLfloat angle_y = 0.0;
GLfloat angle_x = 0.0;
GLfloat pos_x = 0.0;
GLfloat pos_y = 0.0;
GLfloat zoom = -7.0;

int refreshMills = 15;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(pos_x, pos_y, zoom);
    glRotatef(angle_x, 0.0, 1.0, 0.0);
    glRotatef(angle_y, 1.0, 0.0, 0.0);
    
    
    glBegin(GL_QUADS);
    
    glColor3f(0.0, 1.0, 0.0);    // Color Green - TOP
    
    glVertex3f(1.0, 1.0, 1.0); // TOP-RIGHT-NEAR
    glVertex3f(-1.0, 1.0, 1.0); // TOP-LEFT-NEAR
    glVertex3f(-1.0, 1.0, -1.0); //TOP-LEFT-FAR
    glVertex3f(1.0, 1.0, -1.0); // TOP-RIGHT-FAR
    
    glColor3f(1.0, 0.0, 0.0); // Color RED - Bottom
    
    glVertex3f(1.0, -1.0, 1.0); //BOTTOM-RIGHT-NEAR
    glVertex3f(-1.0, -1.0, 1.0); //BOTTOM-LEFT-NEAR
    glVertex3f(-1.0, -1.0, -1.0); //BOTTOM-LEFT-FAR
    glVertex3f(1.0, -1.0, -1.0); //BOTTOM-RIGHT-FAR
    
    glColor3f(1.0, 1.0, 0.0); // Color Yellow - Back
    
    glVertex3f(1.0, 1.0, -1.0); //TOP-RIGHT-FAR
    glVertex3f(-1.0, 1.0, -1.0); //TOP-LEFT-FAR
    glVertex3f(-1.0, -1.0, -1.0); //BOTTOM-LEFT-FAR
    glVertex3f(1.0, -1.0, -1.0); //BOTTOM-RIGHT-FAR
    
    glColor3f(0.0, 0.0, 1.0); //Color Blue - RIGHT
    
    glVertex3f(1.0, 1.0, 1.0); //TOP-FRONT-NEAR
    glVertex3f(1.0, 1.0, -1.0); //TOP-BACK-FAR
    glVertex3f(1.0, -1.0, -1.0); //BOTTOM-BACK-FAR
    glVertex3f(1.0, -1.0, 1.0); //BOTTOM-FRONT-NEAR
    
    glColor3f(1.0, 0.5, 0.0); //Color Orange - Left
    
    glVertex3f(-1.0, 1.0, 1.0); //TOP-FRONT-NEAR
    glVertex3f(-1.0, 1.0, -1.0); //TOP-BACK-FAR
    glVertex3f(-1.0, -1.0, -1.0);//BOTTOM-BACK-FAR
    glVertex3f(-1.0, -1.0, 1.0); //BOTTOM-FRONT-NEAR
    
    glColor3f(1.0, 0.0, 1.0);  // magenta
    
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glEnd();
    
    
    
    glPopMatrix();
    glutSwapBuffers();
}

// инициализируем
void initGL() {
    glClearColor(0.5, 0.5, 0.5, 0.5); // цвет фона
    glClearDepth(1.0);                   // глубина фона
    glEnable(GL_DEPTH_TEST);   // врубаем depth test
    glDepthFunc(GL_LEQUAL);    // тип depth test
    glShadeModel(GL_SMOOTH);   //
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //
}

void process_Normal_Keys(unsigned char key, int x, int y) {
    
    switch (key) {
            
            // rot_x
        case ('a'):
            angle_x -= 10;
            break;
            
        case ('d'):
            angle_x += 10;
            break;
            
            // rot_y
        case ('w'):
            angle_y -= 10;
            break;
            
        case ('s'):
            angle_y += 10;
            break;
            
            // zoom
        case ('z'):
            zoom += 1;
            break;
            
        case ('x'):
            zoom -= 1;
            break;
            
        default:
            break;
            
            // pos_x
        case ('q'):
            pos_x -= 0.1;
            break;
            
        case ('e'):
            pos_x += 0.1;
            break;
            
            // pos_y
        case ('r'):
            pos_y += 0.1;
            break;
            
        case ('f'):
            pos_y -= 0.1;
            break;
            
    }
    
}

void reshape(GLsizei width, GLsizei height) {
    
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    
    
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(45.0, aspect, 0.1, 100.0);
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(refreshMills, timer, 0);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480); // размеры окна
    glutInitWindowPosition(100, 100); // позиция окна на экране
    glutCreateWindow(title); // создаём окно
    
    initGL();
    
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(process_Normal_Keys);
    
    glutMainLoop();
    
    return 0;
}

