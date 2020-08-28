#include "inc/NCraftMain.h"

#include<iostream>
#include<string>


const std::string VERSION = "0.02";
int NCraftWindow::WIDTH = 1000;
int NCraftWindow::HEIGHT = 1000;

NCraftMain::NCraftMain(){
  std::cout << "NCraft v" + VERSION + "\n©Shahan Neda (https://shahan.ca)"<< std::endl;
  NCraftWindow w(1000, 1000, &window);

  initOpenGL();
  mainLoop();
  cleanUp();
}


void NCraftMain::initOpenGL(){
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
  }   
  glViewport(0, 0, NCraftWindow::WIDTH, NCraftWindow::HEIGHT); 
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

  processInput(window);

} 
void NCraftMain::mainLoop(){
  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);



    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

void NCraftMain::processInput(GLFWwindow *window)
{
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void NCraftMain::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
  NCraftWindow::WIDTH = width;
  NCraftWindow::HEIGHT = height;
} 

void NCraftMain::cleanUp(){
  glfwDestroyWindow(window);
  glfwTerminate();
}


int main(){
  NCraftMain m;
  return 0;
}
