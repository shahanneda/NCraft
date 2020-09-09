
#include "NCraftMain.h"
#include <iostream>
#include <string>
#include <glad/glad.h>
#include "graphics/MasterRenderer.h"
#include <string>

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
  if (key == GLFW_KEY_C && status == GLFW_PRESS)
  {
    world->GenerateChunks();
  }
  if ((key == GLFW_KEY_X && status == GLFW_PRESS))
  {
    world->BreakBlock();
  }
}
void NCraftMain::MouseButtonPressed(int key, int status)
{
  if (key == GLFW_MOUSE_BUTTON_LEFT && status == GLFW_PRESS)
  {
    world->BreakBlock();
  }

  if (key == GLFW_MOUSE_BUTTON_RIGHT && status == GLFW_PRESS)
  {
    world->PlaceBlock();
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

  camera = new Camera(glm::vec3(0, 100, 3));
  renderer = new MasterRenderer(window, camera);
  world = new World(renderer, camera);
}
void NCraftMain::mainLoop()
{
  const double frameRateInterval = 1.0;
  int frameCount = 0;
  double frameRate = 0;
  while (!glfwWindowShouldClose(window))
  {
    if (glfwGetTime() > lastFrameRateUpdateTime + frameRateInterval)
    {
      lastFrameRateUpdateTime = glfwGetTime();
      frameRate = frameCount / frameRateInterval;
      frameCount = 0;
    }
    frameCount++;

    deltaTime = glfwGetTime() - lastFrameTime;
    lastFrameTime = glfwGetTime();

    std::string cords = "x: " + std::to_string(camera->position.x) + " y: " + std::to_string(camera->position.y) + " z: " + std::to_string(camera->position.z) + " Chunks Loaded: " + std::to_string(world->cLoader->loadedChunks.size()) + " Queue Of Chunks to load: " + std::to_string(world->cLoader->queueOfChunksToLoad.size()) + " ";

    // glfwSetWindowTitle(window, ("NCraft || " + cords + " || FPS: " + std::to_string(std::ceil(frameRate))).c_str());

    renderer->Render();
    world->Update(deltaTime, glfwGetTime()); // TODO: move this somewhere at a constant time interval
    processInput();
    glfwPollEvents();
  }
}
void NCraftMain::processInput()
{
  if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  const float cameraSpeed = 20.0f * deltaTime;
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera->TranslateCameraBy(cameraSpeed * camera->target);

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera->TranslateCameraBy(-(cameraSpeed * camera->target));

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera->TranslateCameraBy(-glm::normalize(glm::cross(camera->target, camera->up)) * cameraSpeed);

  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera->TranslateCameraBy(glm::normalize(glm::cross(camera->target, camera->up)) * cameraSpeed);

  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    camera->TranslateCameraBy(glm::vec3(0, 1.0f * cameraSpeed, 0));

  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    camera->TranslateCameraBy(glm::vec3(0, -1.0f * cameraSpeed, 0));
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
  delete world;

  glfwDestroyWindow(window);
  glfwTerminate();
}

int main()
{
  NCraftMain m;
  return 0;
}
