#ifndef N_CRAFT_MAIN
#define N_CRAFT_MAIN

#include <Renderer.h>
#include <glad/glad.h>
class Renderer; // forward dec
class NCraftMain
{
public:
  NCraftMain();
  void KeyPressed(int key, int status);

private:
  GLFWwindow *window;
  Renderer *renderer;

  void initOpenGL();
  void mainLoop();
  void cleanUp();

  void processInput();
};
#endif