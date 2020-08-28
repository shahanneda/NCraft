#include "inc/NCraftMain.h"

#include<iostream>
#include<string>


const string VERSION = "0.02";
NCraftMain::NCraftMain(){
  std::cout << "NCraft v" + VERSION + "\n©Shahan Neda (https://shahan.ca)"<< std::endl;
  NCraftWindow w(1000, 1000, &window);

}


void initOpenGL::NCraftMain(){

}

void mainLoop::NCraftMain(){
  while (!glfwWindowShouldClose(window))
  {
        glfwPollEvents();
  }
}

void cleanUp::NCraftMain(){
  glfwDestroyWindow(window);
  glfwTerminate();
}


int main(){
  NCraftMain m;
  return 0;
}
