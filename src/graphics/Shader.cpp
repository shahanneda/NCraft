#include "Shader.h"
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
    std::stringstream ss;
    char log[512];

    // Vertex Shader
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::fstream vfile(vertexPath);
    if (vfile.good())
    {
        ss << vfile.rdbuf();
        std::string str = ss.str();
        const GLchar *g = str.c_str();
        glShaderSource(vertexShader, 1, &g, nullptr);
        glCompileShader(vertexShader);
        glGetShaderInfoLog(vertexShader, 512, nullptr, log);
        std::cout << "Vertex Shader: " << log << std::endl;
    }
    else
    {
        std::cout << "Bad path " << vertexPath.c_str() << std::endl;
    }
    //Fragment Shader
    ss.str("");
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::fstream fFile(fragmentPath);
    if (vfile.good())
    {
        ss << fFile.rdbuf();
        std::string str = ss.str();
        const GLchar *g = str.c_str();
        glShaderSource(fragmentShader, 1, &g, nullptr);
        glCompileShader(fragmentShader);
        glGetShaderInfoLog(fragmentShader, 512, nullptr, log);
        std::cout << "Frag Shader: " << log << std::endl;
    }
    else
    {
        std::cout << "Bad path " << fragmentPath.c_str() << std::endl;
    }

    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);

    glGetProgramInfoLog(id, 512, NULL, log);
    std::cout << "Program: " << log << std::endl;

    // glGetProgramiv(id, GL_LINK_STATUS, &success);
    // if (!success)
    // {
    //     std::cout << "SHADER CREATION ERROR: PROGRAM LINK FAILED\n"
    //               << infoLog << std::endl;
    // }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Bind()
{
    glUseProgram(id);
}

void Shader::setBool(const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value)
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::setVec4f(const std::string &name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}
void Shader::setVec3f(const std::string &name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}
void Shader::setMat4f(const std::string &name, const glm::mat4 mat)
{
    int loc = glGetUniformLocation(id, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));
}
