#pragma once
#include <vector>
#include <Buffer.h>
#include <NCraftWindow.h>
#include <glad/glad.h>

class Renderer
{
public:
  Renderer(GLFWwindow **window);
  ~Renderer();
  void Render();
  void ToggleWireframe();

private:
  VertexBuffer *vertexBuffer;
  GLFWwindow *window;
  unsigned int shaderProgram;
  bool shouldWireframe = false;
};
