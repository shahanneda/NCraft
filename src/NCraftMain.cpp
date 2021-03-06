#ifdef _WIN32
#include <direct.h>
#define getcwd _getcwd // stupid MSFT "deprecation" warning
#else
#include <unistd.h>
#endif

#include "NCraftMain.h"
#include <iostream>
#include <string>
#include <glad/glad.h>
#include "graphics/MasterRenderer.h"
#include <filesystem>
#include <string>

const std::string VERSION = "0.02";
int NCraftWindow::WIDTH = 1000;
int NCraftWindow::HEIGHT = 1000;

NCraftMain::NCraftMain()
{
  std::cout << "NCraft v" + VERSION + "\n©Shahan Neda (https://shahan.ca)" << std::endl;
  NCraftWindow w(1000, 1000, &window, this);
  char buffer[1000];
  char *answer = getcwd(buffer, sizeof(buffer));
  std::string s_cwd;
  if (answer)
  {
    s_cwd = answer;
    std::cout << s_cwd << std::endl;
  }

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
  if (key == GLFW_KEY_F && status == GLFW_PRESS)
  {
    this->noClip = !this->noClip;
  }
  if (key == GLFW_KEY_C && status == GLFW_PRESS)
  {
    world->GenerateChunks();
  }
  if ((key == GLFW_KEY_X && status == GLFW_PRESS))
  {
    world->BreakBlock();
  }

  // Item switching
  if (key >= GLFW_KEY_1 && key <= GLFW_KEY_9 && status == GLFW_PRESS)
  {
    player->SwitchToItemNumber(key - 49); // -49 to map 1-9 keys to 0-8
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

  player = new Player();
  renderer = new MasterRenderer(window, player);
  world = new World(renderer, player);
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

    std::string cords = "x: " + std::to_string(player->camera.position.x) + " y: " + std::to_string(player->camera.position.y) + " z: " + std::to_string(player->camera.position.z) + " Chunks Loaded: " + std::to_string(world->cLoader->loadedChunks.size()) + " Queue Of Chunks to load: " + std::to_string(world->cLoader->queueOfChunksToLoad.size()) + " ";

    // glfwSetWindowTitle(window, ("NCraft || " + cords + " || FPS: " + std::to_string(std::ceil(frameRate))).c_str());

    renderer->Render();
    world->Update(deltaTime, glfwGetTime()); // TODO: move this somewhere at a constant time interval
    processInput();
    processGravity();
    glfwPollEvents();
  }
}
void NCraftMain::processInput()
{
  if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  Camera *camera = &player->camera;
  const float cameraSpeed = 30.0f * deltaTime;

  vec3 translation = vec3(0, 0, 0);

  // forward
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    translation = cameraSpeed * camera->target;

  // backwards
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    translation = -(cameraSpeed * camera->target);

  // right
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    translation = -glm::normalize(glm::cross(camera->target, camera->up)) * cameraSpeed;

  // left
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    translation = glm::normalize(glm::cross(camera->target, camera->up)) * cameraSpeed;

  // up
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    translation = glm::vec3(0, 1.0f * cameraSpeed, 0);

  // down
  if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    translation = glm::vec3(0, -1.0f * cameraSpeed, 0);

  // check if we can actually move there
  if (noClip || world->GetBlockNearPlayer(translation)->type == AIR)
    camera->TranslateCameraBy(translation);
}

void NCraftMain::processGravity()
{
  if (noClip)
    return;

  Camera *camera = &player->camera;
  const float fallSpeed = 5.f * deltaTime;

  Block *blockUnderPlayer = world->GetBlockNearPlayer(vec3(0, -2, 0));
  if (blockUnderPlayer == nullptr || blockUnderPlayer->type == AIR)
  {
    camera->TranslateCameraBy(glm::vec3(0, -1.0f * fallSpeed, 0));
  }
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

  player->camera.setYaw(player->camera.getYaw() + xoffset);
  player->camera.setPitch(player->camera.getPitch() + yoffset);
}

void NCraftMain::cleanUp()
{
  delete renderer;
  delete player;
  delete world;

  glfwDestroyWindow(window);
  glfwTerminate();
}

int main()
{
  NCraftMain m;
  return 0;
}
