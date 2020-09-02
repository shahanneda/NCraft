// ©2020 Shahan Neda

#include "inc/NCraftWindow.h"
#include <iostream>

void NCraftWindow::error_callback(int error, const char *description)
{
  fprintf(stderr, "GLFW Error: %s\n", description);
}

void NCraftWindow::NCraftMouseCallback(GLFWwindow *window, double xpos, double ypos)
{
  main->MouseMoved(xpos, ypos);
}

void NCraftWindow::NCraftKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{

  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }
  main->KeyPressed(key, action);
}
void NCraftWindow::WindowResized(int width, int height)
{
  glViewport(0, 0, width, height);
  NCraftWindow::WIDTH = width;
  NCraftWindow::HEIGHT = height;
}
NCraftWindow::NCraftWindow(int width, int height, GLFWwindow **window, NCraftMain *main)
{
  this->main = main;
  std::cout << "NCraftWindow: Init" << std::endl;

  if (!glfwInit())
  {
    throw std::runtime_error("GLFW INIT FAILED!");
  }
  glfwSetErrorCallback(error_callback);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  *window = glfwCreateWindow(width, height, "NCraft", NULL, NULL);

  if (!*window)
  {
    throw std::runtime_error("GLFW WINDOW CREATION FAILED!");
  }

  // Setup call backs for glfw
  glfwSetWindowUserPointer(*window, this);
  glfwSetKeyCallback(*window, key_callback);
  glfwSetCursorPosCallback(*window, mouse_callback);
  glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);

  glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwMakeContextCurrent(*window);
}
