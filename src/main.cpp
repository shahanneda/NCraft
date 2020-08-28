#include "inc/NCraftMain.h"

#include<iostream>
#include<string>
#include <glad/glad.h> 

const std::string VERSION = "0.02";
NCraftMain::NCraftMain(){
  std::cout << "NCraft v" + VERSION + "\n©Shahan Neda (https://shahan.ca)"<< std::endl;
  NCraftWindow w(1000, 1000, &window);

  initOpenGL();
  mainLoop();
  cleanUp();
}


void NCraftMain::initOpenGL(){

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
