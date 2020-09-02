#include <Renderer.h>
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
using glm::vec2;
using glm::vec3;
// #include <Texture.h>

std::vector<int> indices = {
    0, 1, 2, //  front face
    2, 3, 0, //

    2, 6, 7, // right side
    2, 7, 3, //

    6, 5, 4, // back face
    5, 4, 7, //

    5, 4, 0, // left side
    5, 0, 1, //

    1, 2, 6, // top side
    1, 6, 5, //

    0, 3, 7, // bottom side
    1, 7, 4  //
};
// glBindBuffer(GL_ARRAY_BUFFER, VBO);
Renderer::Renderer(GLFWwindow **window)
{
  this->window = *window;
  vertexBuffer = new VertexBuffer();
  mainShader = new Shader("shaders/shader.vert", "shaders/shader.frag");

  std::vector<vec3> vertices = {
      vec3(0, 0, 0), // 0 bottom left
      vec3(0, 1, 0), // 1 top left
      vec3(1, 1, 0), // 2 top right
      vec3(1, 0, 0), // 3 bottom right

      vec3(0, 0, 1), // 4 bottom left
      vec3(0, 1, 1), // 5 top left
      vec3(1, 1, 1), // 6 top right
      vec3(1, 0, 1), // 7 bottom right

  };

  std::vector<vec2> texCoords = {
      vec2(0, 0),
      vec2(0, 1),
      vec2(1, 1),
      vec2(1, 0),

      vec2(0, 0),
      vec2(0, 1),
      vec2(1, 1),
      vec2(1, 0),
  };

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
  model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 1.0f, 0.0f));
  ;
  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

  glm::mat4 projection;

  // fov / aspectratio/ near clip / far clip TODO: add option for these things TODO: add aspect ration height/width
  projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

  mainShader->setMat4f("model", model);
  mainShader->setMat4f("view", view);
  mainShader->setMat4f("projection", projection);

  glPolygonMode(GL_FRONT_AND_BACK, (shouldWireframe) ? GL_LINE : GL_FILL);
  float timeValue = glfwGetTime();
  float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
  // mainShader->setVec4f("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

  // this draws using the incides, 6 is number of indices, gl unsined int is type
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

  glfwSwapBuffers(window);
}
