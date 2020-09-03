#pragma once
#include <vector>
#include "Buffer.h"
#include "NCraftWindow.h"
#include <glad/glad.h>
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include <glm/glm.hpp>
#include "../world/Block.h"
#include "WorldRenderer.h"

class MasterRenderer
{
public:
  MasterRenderer(GLFWwindow **window, Camera **camera);
  ~MasterRenderer();
  void Render();
  void ToggleWireframe();

private:
  GLFWwindow *window;
  bool shouldWireframe = false;
  Camera *camera;
  WorldRenderer *worldRenderer;
};