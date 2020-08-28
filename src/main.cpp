#include "inc/NCraftMain.h"
#include "inc/NCraftWindow.h"

#include<iostream>


NCraftMain::NCraftMain(){
  std::cout << "NCraft v0.01" << std::endl;
  NCraftWindow w(1000, 1000);
}


int main(){
  NCraftMain m;
  return 0;
}
