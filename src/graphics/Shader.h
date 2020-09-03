#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>

class Shader
{
public:
    uint32_t id;

    Shader(const std::string vertexPath, const std::string fragmentPath);

    void Bind();
    // utility uniform functions
    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setVec4f(const std::string &name, float x, float y, float z, float w);
    void setMat4f(const std::string &name, const glm::mat4 mat);
};

#endif