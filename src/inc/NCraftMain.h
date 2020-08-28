#include "NCraftWindow.h"

class NCraftMain{
  public: 
    static int WIDTH ; 
    static int HEIGHT;
    NCraftMain();

  private:
    GLFWwindow* window;
    void initOpenGL();
    void mainLoop();
    void cleanUp();
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow* window);

};

