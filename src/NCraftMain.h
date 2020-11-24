#ifndef N_CRAFT_MAIN
#define N_CRAFT_MAIN

#include "graphics/MasterRenderer.h"
#include <glad/glad.h>
#include "world/World.h"
#include "player/Player.h"

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
  bool noClip = false;

  void MouseMoved(double xpos, double ypos);
  void MouseButtonPressed(int button, int action);


private:
  const float mouseSensitivity = 0.1f;
  GLFWwindow *window;
  World *world;
  MasterRenderer *renderer;
  Player *player;

  float lastMouseX = -999;
  float lastMouseY = -999;

  float lastFrameRateUpdateTime = 0;

  void
  initOpenGL();
  void mainLoop();
  void processGravity();
  void cleanUp();

  void processInput();
};
#endif