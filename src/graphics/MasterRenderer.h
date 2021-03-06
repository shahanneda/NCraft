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
#include "ui/UIRenderer.h"
#include "../player/Player.h"

class MasterRenderer
{
public:
  MasterRenderer(GLFWwindow *window, Player *player);
  ~MasterRenderer();
  void Render();
  void ToggleWireframe();
  WorldRenderer *worldRenderer;
  UIRenderer *uiRenderer;

private:
  GLFWwindow *window;
  bool shouldWireframe = false;
  Player *player;
};
