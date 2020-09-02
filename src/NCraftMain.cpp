
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

  camera = new Camera(glm::vec3(0, 0, 3));
  renderer = new Renderer(&window, &camera);
}
void NCraftMain::mainLoop()
{
  while (!glfwWindowShouldClose(window))
  {
    deltaTime = glfwGetTime() - lastFrameTime;
    lastFrameTime = glfwGetTime();

    renderer->Render();
    processInput();
    glfwPollEvents();
  }
}
void NCraftMain::processInput()
{
  if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  const float cameraSpeed = 2.5f * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera->TranslateCameraBy(cameraSpeed * camera->target);

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera->TranslateCameraBy(-(cameraSpeed * camera->target));

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera->TranslateCameraBy(-glm::normalize(glm::cross(camera->target, camera->up)) * cameraSpeed);

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera->TranslateCameraBy(glm::normalize(glm::cross(camera->target, camera->up)) * cameraSpeed);
}

void NCraftMain::MouseMoved(double xpos, double ypos)
{
  if (lastMouseX == -999)
  { // check if first time moving mouse
    lastMouseX = xpos;
    lastMouseY = ypos;
  }
  float xoffset = xpos - lastMouseX;
  float yoffset = lastMouseY - ypos; // y from bottom to top
  lastMouseX = xpos;
  lastMouseY = ypos;

  xoffset *= mouseSensitivity;
  yoffset *= mouseSensitivity;

  camera->setYaw(camera->getYaw() + xoffset);
  camera->setPitch(camera->getPitch() + yoffset);
}

void NCraftMain::cleanUp()
{
  delete renderer;
  delete camera;

  glfwDestroyWindow(window);
  glfwTerminate();
}

int main()
{
  NCraftMain m;
  return 0;
}
