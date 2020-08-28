#include <Renderer.h>
#include <iostream>

// glBindBuffer(GL_ARRAY_BUFFER, VBO);
Renderer::Renderer(GLFWwindow **window)
{
  this->window = *window;
  vertexBuffer = new VertexBuffer();

  glUseProgram(shaderProgram);

  std::vector<Vec3f> vertices = {
      Vec3f(0.5f, 0.5f, 0.0f),
      Vec3f(0.5f, -0.5f, 0.0f),
      Vec3f(-0.5f, -0.5f, 0.0f),
      Vec3f(-0.5f, 0.5f, 0.0f)

  };
  std::vector<int> indices = {
      0, 1, 3,
      1, 2, 3};
  vertexBuffer->BindVertexArrayBuffer();
  vertexBuffer->PutVertexData(vertices, indices);
}

void Renderer::ToggleWireframe()
{
  std::cout << "Renderer: Toggling Wireframe Mode" << std::endl;
  shouldWireframe = !shouldWireframe;
}

Renderer::~Renderer()
{
  delete vertexBuffer;
}

void Renderer::Render()
{
  // clear the screen
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(shaderProgram);
  vertexBuffer->BindVertexArrayBuffer(); // bind our array object

  if (shouldWireframe)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }
  else
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }

  // this draws using the incides, 6 is number of indices, gl unsined int is type
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glfwSwapBuffers(window);
}
