// Shahan Neda  ©2020
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../NCraftMain.h"

class NCraftMain;
class NCraftWindow
{
public:
  static int WIDTH;
  static int HEIGHT;
  NCraftMain *main;

  NCraftWindow(int width, int height, GLFWwindow **window, NCraftMain *main);
  // GLFW CALLBACK WRAPPERS
  static void error_callback(int error, const char *description);
  inline static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
  {
    NCraftWindow *w = static_cast<NCraftWindow *>(glfwGetWindowUserPointer(window));
    w->NCraftKeyCallback(window, key, scancode, action, mods);
  }
  inline static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
  {
    NCraftWindow *w = static_cast<NCraftWindow *>(glfwGetWindowUserPointer(window));
    w->WindowResized(width, height);
  }
  inline static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
  {
    NCraftWindow *w = static_cast<NCraftWindow *>(glfwGetWindowUserPointer(window));
    w->NCraftMouseButtonCallback(window, button, action, mods);
  }

  void NCraftMouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

  void NCraftMouseCallback(GLFWwindow *window, double xpos, double ypos);

  inline static void mouse_callback(GLFWwindow *window, double xpos, double ypos)
  {
    NCraftWindow *w = static_cast<NCraftWindow *>(glfwGetWindowUserPointer(window));
    w->NCraftMouseCallback(window, xpos, ypos);
  }

  void WindowResized(int width, int height);
  void NCraftKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
};
