#ifndef N_CRAFT_MAIN
#define N_CRAFT_MAIN

#include <Renderer.h>
#include <glad/glad.h>

class Camera;   // forward dec
class Renderer; // forward dec
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
  Renderer *renderer;
  Camera *camera;

  float lastMouseX = -999;
  float lastMouseY = -999;

  void initOpenGL();
  void mainLoop();
  void cleanUp();

  void processInput();
};
#endif