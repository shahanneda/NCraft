#ifndef N_CRAFT_MAIN
#define N_CRAFT_MAIN

#include "graphics/MasterRenderer.h"
#include <glad/glad.h>
#include "world/World.h"

class Camera;         // forward dec
class MasterRenderer; // forward dec
class World;
class NCraftMain
{
public:
  NCraftMain();
  void KeyPressed(int key, int status);
  float deltaTime = 0;
  float lastFrameTime = 0;
  void MouseMoved(double xpos, double ypos);

private:
  const float mouseSensitivity = 0.1f;
  GLFWwindow *window;
  World *world;
  MasterRenderer *renderer;
  Camera *camera;

  float lastMouseX = -999;
  float lastMouseY = -999;

  void initOpenGL();
  void mainLoop();
  void cleanUp();

  void processInput();
};
#endif