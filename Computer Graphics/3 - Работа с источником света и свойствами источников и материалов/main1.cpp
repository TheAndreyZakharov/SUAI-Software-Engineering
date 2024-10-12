#define _CRT_SECURE_NO_WARNINGS
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <GLUT/glut.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>
#include "Shader.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 lightPos(1.5f, 0.0f, 2.0f);

static const GLfloat vertices[] = {
    //   позиция        |    нормаль
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
    
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
    
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
    
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
    
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
    
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f),
    glm::vec3( 1.5f,  0.0f, 0.0f),
    glm::vec3(-1.5f,  0.0f, 0.0f)
};

void processInput(GLFWwindow *window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);


int main() {
    //************************************************************************************
    // GLFW
    if(!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    // Минимальная требуемая версия OpenGL.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Установка профайла для которого создается контекст
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Возможность изменения размера окна
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CG-Lab-OGL3x", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // GLXW
    if(glxwInit()) {
        std::cerr << "Failed to init GLXW" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //************************************************************************************
    // SETTINGS SHADERS
    Shader Program{};
    Program.loadShader("vShader.glsl", GL_VERTEX_SHADER);
    Program.loadShader("fShader.glsl", GL_FRAGMENT_SHADER);
    Program.linkShaders();
    
    // SETTINGS BUFFERS
    GLuint VBO; // Объект вершинного буфера
    GLuint VAO; // Объект вершинного массива
    
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    
    
    glBindVertexArray(VAO);
    // Копируем массив с вершинами в буфер OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Установим указатели на вершинные атрибуты
    glVertexAttribPointer(
                          0, // какой аргумент шейдера хотим настроить
                          3, // размер аргумента в шейдере (vec3)
                          GL_FLOAT, // используемый тип данных
                          GL_FALSE, // необходимость нормализовать входные данные
                          6 * sizeof(float), //шаг (описывает расстояние между наборами данных)
                          nullptr); // смещение начала данных в буфере
    
    glEnableVertexAttribArray(0);
    
    // Устанавливаем указатели на вектор нормали
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    glEnable(GL_DEPTH_TEST);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // Игровой цикл
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        Program.use();
        
        GLfloat radius = 5.0f;
        GLfloat camX = sin(glfwGetTime()) * radius;
        GLfloat camY = 2.0;
        GLfloat camZ = cos(glfwGetTime()) * radius;
        glm::vec3 cameraPos (camX, camY, camZ);
        
        Program.setVec3("light.position", lightPos);
        Program.setVec3("viewPos", cameraPos);
        
        // Нстройка параметров источника света
        Program.setVec3("light.ambient",  0.99f, 0.99f, 0.99f);
        Program.setVec3("light.diffuse", 0.99f, 0.99f, 0.99f);
        Program.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        
        glm::mat4 view;
        glm::mat4 projection;
        
        view = glm::lookAt( glm::vec3(cameraPos), // Положение камеры
                           glm::vec3(0.0f, 0.0f, 0.0f), // Направление камеры (смотрит в точку (0,0,0))
                           glm::vec3(0.0f, 1.0f, 0.0f)); // Камера расположена горизонтально
        
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        
        
        Program.setMat4("view", view);
        Program.setMat4("projection", projection);
        
        glBindVertexArray(VAO);
        
        //~~~~~~~~~~~~~~~~~~ CUBE-1 ambient ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Program.setVec3("material.ambient", 0.8f, 0.8f, 0.2f);
        Program.setVec3("material.diffuse", 0.0f, 0.0f, 0.0f);
        Program.setVec3("material.specular", 0.0f, 0.0f, 0.0f);
        Program.setFloat("material.shininess", 32.0f);
        
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[0]);
        Program.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //~~~~~~~~~~~~~~~~~~ CUBE-2 diffuse ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Program.setVec3("material.ambient", 0.2f, 0.0f, 0.0f);
        Program.setVec3("material.diffuse", 0.8f, 0.0f, 0.0f);
        Program.setVec3("material.specular", 0.0f, 0.0f, 0.0f);
        Program.setFloat("material.shininess", 32.0f);
        
        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2, cubePositions[1]);
        Program.setMat4("model", model2);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        //~~~~~~~~~~~~~~~~~~ CUBE-3 specular ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        Program.setVec3("material.ambient", 0.0f, 0.03f, 0.0f);
        Program.setVec3("material.diffuse", 0.0f, 0.03f, 0.0f);
        Program.setVec3("material.specular", 0.0f, 0.8f, 0.0f);
        Program.setFloat("material.shininess", 16.0f);
        
        glm::mat4 model3 = glm::mat4(1.0f);
        model3 = glm::translate(model3, cubePositions[2]);
        Program.setMat4("model", model3);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        glfwSwapBuffers(window); // Заменяет цветовой буфер
        /* Передний буфер - результирующее изображение
         * Задний буфер - отрисовка.
         * Как только отрисовка будет закончена, эти буферы меняются местами
         * */
        glfwPollEvents(); // Проверка события
    }
    
    // Очистка ресурсов
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

//-----------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
//-----------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
//-----------------------------------------------------------------------------------
