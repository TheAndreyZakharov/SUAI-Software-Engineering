#ifndef CG_LABS_OGL3X_SHADER_H
#define CG_LABS_OGL3X_SHADER_H

#include <GLUT/glut.h>
//#include <GLXW/glxw.h> //Лоадер OpenGL
//#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
    
public:
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint id;
    
public:
    GLuint loadShader(const char* fileName, GLenum shaderType);
    void linkShaders();
    void use() const;
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z);
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w) const;
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    
private:
    void checkCompileErrors(GLuint shader, std::string type);
};

GLuint Shader::loadShader(const char* fileName, GLenum shaderType) {
    std::ifstream shaderFile;
    std::string shaderCode;
    shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        shaderFile.open(fileName);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* shaderSourceCStr = shaderCode.c_str();
    
    GLuint shaderId = glCreateShader(shaderType);
    if (shaderType == GL_VERTEX_SHADER) {
        this->vertexShader = shaderId;
    } else if (shaderType == GL_FRAGMENT_SHADER) {
        this->fragmentShader = shaderId;
    }
    
    glShaderSource(
                   shaderId, // шейдер, который требуется собрать
                   1, // количество строк.
                   &shaderSourceCStr, // исходный код шейдера
                   nullptr);
    
    glCompileShader(shaderId);
    checkCompileErrors(shaderId, "SHADER");
    return shaderId;
}
//-------------------------------------------------------------------------------------

void Shader::checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog
            << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog
            << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
//-------------------------------------------------------------------------------------

void Shader::linkShaders() {
    /*
     * При соединении шейдеров в программу,
     * выходные значения одного шейдера сопоставляются с входными значениями другого шейдера
     */
    this->id = glCreateProgram();
    glAttachShader(this->id, this->vertexShader);
    glAttachShader(this->id, this->fragmentShader);
    glLinkProgram(this->id);
    
    checkCompileErrors(this->id, "PROGRAM");
    
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
}

// activate the Shader
// ------------------------------------------------------------------------
void Shader::use() const
{
    glUseProgram(this->id);
}
// utility uniform functions
// ------------------------------------------------------------------------
void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(this->id, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(this->id, name.c_str()), value);
}
// ------------------------------------------------------------------------
void Shader::setVec2(const std::string &name, const glm::vec2 &value) const
{
    glUniform2fv(glGetUniformLocation(this->id, name.c_str()), 1, &value[0]);
}
void Shader::setVec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(this->id, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void Shader::setVec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(this->id, name.c_str()), 1, &value[0]);
}
void Shader::setVec3(const std::string &name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(this->id, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void Shader::setVec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(this->id, name.c_str()), 1, &value[0]);
}
void Shader::setVec4(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(this->id, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void Shader::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(this->id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
#endif //CG_LABS_OGL3X_SHADER_H
