// Shahan Neda  ©2020
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class NCraftWindow
{
public:
  static int WIDTH;
  static int HEIGHT;
  NCraftWindow(int width, int height, GLFWwindow **window);
};
