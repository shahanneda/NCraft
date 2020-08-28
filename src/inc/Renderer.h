#pragma once
#include <vector>
#include <Buffer.h>
#include <NCraftWindow.h>
#include <glad/glad.h>
#include <Shader.h>

class Renderer
{
public:
  Renderer(GLFWwindow **window);
  ~Renderer();
  void Render();
  void ToggleWireframe();

private:
  Shader *mainShader;
  VertexBuffer *vertexBuffer;
  GLFWwindow *window;
  unsigned int shaderProgram;
  bool shouldWireframe = false;
};
