#include "NCraftWindow.h"

class NCraftMain{
  public: 
    NCraftMain();
  
  private:
    GLFWwindow* window;
    void initOpenGL();
    void mainLoop();
    void cleanUp();

};

