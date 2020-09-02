#include <Renderer.h>
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

// #include <Texture.h>

// glBindBuffer(GL_ARRAY_BUFFER, VBO);
Renderer::Renderer(GLFWwindow **window)
{
  this->window = *window;
  vertexBuffer = new VertexBuffer();
  mainShader = new Shader("shaders/shader.vert", "shaders/shader.frag");

  std::vector<Vec3f> vertices = {
      Vec3f(0.5f, 0.5f, 0.0f),
      Vec3f(0.5f, -0.5f, 0.0f),
      Vec3f(-0.5f, -0.5f, 0.0f),
      Vec3f(-0.5f, 0.5f, 0.0f)};
  std::vector<int> indices = {
      0, 1, 3,
      1, 2, 3};

  std::vector<float> texCoords = {
      1.0f, 1.0f, // lower-left corner
      1.0f, 0.0f, // lower-right corner
      0.0f, 0.0f, // top-center corner
      0.0f, 1.0f};

  texture = new Texture("resources/container.jpg");
  texture->BindTexture();

  mainShader->Bind();
  vertexBuffer->BindVertexArrayBuffer();
  vertexBuffer->PutVertexData(vertices, indices, texCoords);
}

void Renderer::ToggleWireframe()
{
  std::cout << "Renderer: Toggling Wireframe Mode" << std::endl;
  shouldWireframe = !shouldWireframe;
}

Renderer::~Renderer()
{
  delete vertexBuffer;
  delete mainShader;
}

void Renderer::Render()
{
  // clear the screen
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glActiveTexture(GL_TEXTURE0);
  texture->BindTexture();
  mainShader->Bind();
  // mainShader->setFloat("gcolor", 1.0f);

  vertexBuffer->BindVertexArrayBuffer(); // bind our array object
  mainShader->Bind();

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  ;
  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

  mainShader->setMat4f("model", model);
  mainShader->setMat4f("view", view);
  mainShader->setMat4f("projection", projection);

  glPolygonMode(GL_FRONT_AND_BACK, (shouldWireframe) ? GL_LINE : GL_FILL);
  float timeValue = glfwGetTime();
  float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
  // mainShader->setVec4f("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

  // this draws using the incides, 6 is number of indices, gl unsined int is type
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

  glfwSwapBuffers(window);
}
