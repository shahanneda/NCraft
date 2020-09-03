#include "MasterRenderer.h"
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "../world/Chunk.h"
#include <glm/gtx/string_cast.hpp>

using glm::vec2;
using glm::vec3;
// #include <Texture.h>

// glBindBuffer(GL_ARRAY_BUFFER, VBO);
MasterRenderer::MasterRenderer(GLFWwindow **window, Camera **camera)
{
  this->window = *window;
  this->camera = *camera;
  this->worldRenderer = new WorldRenderer();
}

void MasterRenderer::ToggleWireframe()
{
  std::cout << "Renderer: Toggling Wireframe Mode" << std::endl;
  shouldWireframe = !shouldWireframe;
}

MasterRenderer::~MasterRenderer()
{
  delete worldRenderer;
}

void MasterRenderer::Render()
{
  // clear the screen
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPolygonMode(GL_FRONT_AND_BACK, (shouldWireframe) ? GL_LINE : GL_FILL);

  glm::mat4 projection; // from camera to screen
  // fov / aspectratio/ near clip / far clip TODO: add option for these things TODO: add aspect ration height/width
  projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);
  glm::mat4 view = camera->GetViewMatrix();

  worldRenderer->Render(projection, view);
  glfwSwapBuffers(window);
}
