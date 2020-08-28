
#include <NCraftMain.h>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include "NCraftWindow.h"

const std::string VERSION = "0.02";
int NCraftWindow::WIDTH = 1000;
int NCraftWindow::HEIGHT = 1000;

NCraftMain::NCraftMain()
{
  std::cout << "NCraft v" + VERSION + "\n©Shahan Neda (https://shahan.ca)" << std::endl;
  NCraftWindow w(1000, 1000, &window, this);

  initOpenGL();
  mainLoop();
  cleanUp();
}

void NCraftMain::KeyPressed(int key, int status)
{
  // std::cout << "Key pressed " << key << " status " << status << std::endl;
  if (key == GLFW_KEY_Z && status == GLFW_PRESS)
  {
    renderer->ToggleWireframe();
  }
}
void NCraftMain::initOpenGL()
{
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }
  glViewport(0, 0, NCraftWindow::WIDTH, NCraftWindow::HEIGHT);
  // glfwSetKeyCallback(window, key_callback);

  renderer = new Renderer(&window);
}
void NCraftMain::mainLoop()
{
  while (!glfwWindowShouldClose(window))
  {
    renderer->Render();
    processInput();
    glfwPollEvents();
  }
}
void NCraftMain::processInput()
{
  if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void NCraftMain::cleanUp()
{
  delete renderer;

  glfwDestroyWindow(window);
  glfwTerminate();
}

int main()
{
  NCraftMain m;
  return 0;
}
