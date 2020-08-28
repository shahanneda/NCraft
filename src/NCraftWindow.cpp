// ©2020 Shahan Neda

#include "inc/NCraftWindow.h"
#include <iostream>


void error_callback(int error, const char* description)
{
  fprintf(stderr, "GLFW Error: %s\n", description);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}


NCraftWindow::NCraftWindow(int width, int height, GLFWwindow** window){
  std::cout << "NCraftWindow: Init";

  if (!glfwInit())
  {
    throw std::runtime_error("GLFW INIT FAILED!");
  }

  glfwSetErrorCallback(error_callback);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  *window = glfwCreateWindow(width, height, "NCraft", NULL, NULL);


  if (!*window)
  {
    throw std::runtime_error("GLFW WINDOW CREATION FAILED!");
  }

  glfwSetKeyCallback(*window, key_callback);
  glfwMakeContextCurrent(*window);


}
