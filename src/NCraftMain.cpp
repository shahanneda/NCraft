#include "inc/NCraftMain.h"

#include <iostream>
#include <string>

const std::string VERSION = "0.02";
int NCraftWindow::WIDTH = 1000;
int NCraftWindow::HEIGHT = 1000;

NCraftMain::NCraftMain()
{
  std::cout << "NCraft v" + VERSION + "\n©Shahan Neda (https://shahan.ca)" << std::endl;
  NCraftWindow w(1000, 1000, &window);

  initOpenGL();
  mainLoop();
  cleanUp();
}

// VertexBuffer vb;
// unsigned int VAO; // vao basically stores the config of the vbo
void NCraftMain::initOpenGL()
{
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }
  glViewport(0, 0, NCraftWindow::WIDTH, NCraftWindow::HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // unsigned int VBO;
  // glGenBuffers(1, &VBO);
  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  /*
   *GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
GL_STATIC_DRAW: the data is set only once and used many times.
GL_DYNAMIC_DRAW: the data is changed a lot and used many times.
   *
   *
   */
  renderer = new Renderer(&window);
}
void NCraftMain::mainLoop()
{
  while (!glfwWindowShouldClose(window))
  {
    renderer->Render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void NCraftMain::processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void NCraftMain::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  glViewport(0, 0, width, height);
  NCraftWindow::WIDTH = width;
  NCraftWindow::HEIGHT = height;
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
