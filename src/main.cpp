#include "inc/NCraftMain.h"

#include<iostream>


NCraftMain::NCraftMain(){
  std::cout << "NCraft v0.01" << std::endl;

  int x = 10;

  NCraftWindow w(1000, 1000, &window);

  while (!glfwWindowShouldClose(window))
  {
        glfwPollEvents();
  }
  glfwDestroyWindow(window);
  glfwTerminate();
}




int main(){
  NCraftMain m;
  return 0;
}
