
#include <Shader.h>
#include <iostream>

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{

    // const char *vertexShaderSource = "#version 330 core\n"
    //                                  "layout (location = 0) in vec3 aPos;\n"
    //                                  "void main()\n"
    //                                  "{\n"
    //                                  "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    //                                  "}\0";

    // // const char *fragmentShaderSource = "#version 330 core\n"
    //                                    "out vec4 FragColor;\n"
    //                                    "void main()\n"
    //                                    "{\n"
    //                                    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    //                                    "}\n\0";

    std::stringstream ss;
    char log[512];

    // Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
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
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
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

    programId = glCreateProgram();
    glAttachShader(programId, vertexShader);
    glAttachShader(programId, fragmentShader);
    glLinkProgram(programId);

    glGetProgramInfoLog(programId, 512, NULL, log);
    std::cout << "Program: " << log << std::endl;

    // glGetProgramiv(programId, GL_LINK_STATUS, &success);
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
    glUseProgram(programId);
}

void Shader::setBool(const std::string &name, bool value)
{
    glUniform1i(glGetUniformLocation(programId, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value)
{
    glUniform1i(glGetUniformLocation(programId, name.c_str()), (int)value);
}
