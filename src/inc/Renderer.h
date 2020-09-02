#pragma once
#include <vector>
#include <Buffer.h>
#include <NCraftWindow.h>
#include <glad/glad.h>
#include <Shader.h>
#include <Texture.h>
#include <glm/glm.hpp>

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
  uint32_t shaderProgram;
  bool shouldWireframe = false;
  Texture *texture;
};
