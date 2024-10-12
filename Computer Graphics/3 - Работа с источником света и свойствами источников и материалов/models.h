
/*
 Здесь храянтся модели
 */
#include <GLUT/GLUT.h>
#include <iostream>
//#include <GL/freeglut.h>

void model_wall() {
    glBegin(GL_QUADS);
    
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
    
    glEnd();
}

void model_roof() {
    glBegin(GL_QUADS);
    
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 1, 1);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1, 1, 0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1, 0, 0);
    
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 0, 1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 1, 1);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1, 1, 0);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 0, 0);
    
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1, 0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, 0, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 1);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 0, 1);
    
    glVertex3f(1, 1, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(-1, 0, 0);
    glVertex3f(-1, 1, 0);
    
    glEnd();
}
