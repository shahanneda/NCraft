#include <Renderer.h>
#include <iostream>

// glBindBuffer(GL_ARRAY_BUFFER, VBO);
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

Renderer::Renderer(GLFWwindow **window)
{
  this->window = *window;
  vertexBuffer = new VertexBuffer();

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);

  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  //check for errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success)
  {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  int nrAttributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
  std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success)
  {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  glUseProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  std::vector<Vec3f> vertices = {
      Vec3f(0.5f, 0.5f, 0.0f),
      Vec3f(0.5f, -0.5f, 0.0f),
      Vec3f(-0.5f, -0.5f, 0.0f),
      Vec3f(-0.5f, 0.5f, 0.0f)

  };
  std::vector<int> indices = {
      0, 1, 3,
      1, 2, 3};
  vertexBuffer->BindVertexArrayBuffer();
  vertexBuffer->PutVertexData(vertices, indices);
}

void Renderer::ToggleWireframe()
{
  std::cout << "Renderer: Toggling Wireframe Mode" << std::endl;
  shouldWireframe = !shouldWireframe;
}

Renderer::~Renderer()
{
  delete vertexBuffer;
}

void Renderer::Render()
{
  // clear the screen
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(shaderProgram);
  vertexBuffer->BindVertexArrayBuffer(); // bind our array object

  if (shouldWireframe)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  else
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  // this draws using the incides, 6 is number of indices, gl unsined int is type
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glfwSwapBuffers(window);
}
