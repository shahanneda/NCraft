#include <vector>
#include <Buffer.h>
#include <NCraftWindow.h>
class Renderer
{
public:
  Renderer(GLFWwindow **window);
  ~Renderer();
  void Render();

private:
  VertexBuffer *vertexBuffer;
  GLFWwindow *window;
  unsigned int shaderProgram;
};
