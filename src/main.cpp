#include "inc/NCraftMain.h"

#include<iostream>
#include<string>

const int WIDTH = 1000; 
const int HEIGHT = 1000;

const std::string VERSION = "0.02";

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
  glViewport(0, 0, WIDTH, HEIGHT); 
} 
void NCraftMain::mainLoop(){
  while (!glfwWindowShouldClose(window))
  {
    glfwPollEvents();
  }
}

void NCraftMain::cleanUp(){
  glfwDestroyWindow(window);
  glfwTerminate();
}


int main(){
  NCraftMain m;
  return 0;
}
