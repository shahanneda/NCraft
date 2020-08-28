#include <iostream>
#include <GLFW/glfw3.h>


void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}
int main(){
  std::cout << "NCraft V0.01" << std::endl;

  if (!glfwInit())
  {
    std::cout << "GLFW INIT FAILED" << std::endl;
  }

  glfwSetErrorCallback(error_callback);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);

  if (!window)
  {
    std::cout << "GLFW window failed!!" << std::endl;
  }

  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);

  while (!glfwWindowShouldClose(window))
  {
        glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}


