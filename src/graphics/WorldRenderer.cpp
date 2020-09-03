#include "WorldRenderer.h"
#include "Cube.h"
#include "glm/gtc/matrix_transform.hpp"

using glm::vec2;
using glm::vec3;
WorldRenderer::WorldRenderer()
{
    Cube cubeData;
    Chunk *c = new Chunk(); // temp
    worldVertexBuffer = new VertexBuffer();
    worldShader = new Shader("shaders/shader.vert", "shaders/shader.frag");

    worldTexture = new Texture("resources/container.jpg");
    worldTexture->BindTexture();

    worldShader->Bind();
    worldVertexBuffer->BindVertexArrayBuffer();
    worldVertexBuffer->PutVertexData(cubeData.vertices, cubeData.indices, cubeData.texCoords);
}

void WorldRenderer::RenderChunck(Chunk *c)
{
}
void WorldRenderer::Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
    glActiveTexture(GL_TEXTURE0);
    worldTexture->BindTexture();
    worldShader->Bind();

    worldVertexBuffer->BindVertexArrayBuffer();
    worldShader->Bind();

    worldShader->setMat4f("view", viewMatrix);

    worldShader->setMat4f("projection", projectionMatrix);

    for (int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f); // model = local space to world space
        model = glm::translate(model, vec3(i * 2, 0, i));
        model = glm::rotate(model, (float)i, glm::vec3(0.0f, 1.0f, 0.0f));

        worldShader->setMat4f("model", model);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
    }
    this->RenderChunck(c);
}

WorldRenderer::~WorldRenderer()
{
    delete c;
    delete worldVertexBuffer;
    delete worldShader;
    delete worldTexture;
}