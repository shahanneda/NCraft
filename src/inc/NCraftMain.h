#include "NCraftWindow.h"
#include <Renderer.h>

class NCraftMain
{
public:
  NCraftMain();

private:
  GLFWwindow *window;
  Renderer *renderer;

  void initOpenGL();
  void mainLoop();
  void cleanUp();
  static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
  void processInput(GLFWwindow *window);
};
