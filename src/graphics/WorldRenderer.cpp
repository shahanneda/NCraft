#include "WorldRenderer.h"
#include "glm/gtc/matrix_transform.hpp"

using glm::vec2;
using glm::vec3;
WorldRenderer::WorldRenderer()
{
    worldVertexBuffer = new VertexBuffer();
    worldShader = new Shader("shaders/shader.vert", "shaders/shader.frag");
    worldTexture = new Texture("resources/container.jpg");
    ;
    cLoader = new ChunkLoader(this);

    // posx->SetBlock(Block(vec3(0, 5, 5), AIR));
    // posz->SetBlock(Block(vec3(0, 5, 15), AIR));
}

void WorldRenderer::RenderChunck(Chunk *c)
{
    glActiveTexture(GL_TEXTURE0);
    worldTexture->BindTexture();
    worldShader->Bind();
    worldVertexBuffer->BindVertexArrayBuffer();
    worldVertexBuffer->PutVertexData(c->meshData.verts, c->meshData.indices, c->meshData.textureCoords);

    glm::mat4 model = glm::mat4(1.0f); // model = local space to world space
    model = glm::translate(model, vec3(c->pos.x * Chunk::CHUNCK_SIZE, c->pos.y * Chunk::CHUNCK_SIZE, c->pos.z * Chunk::CHUNCK_SIZE));

    worldShader->setMat4f("model", model);
    glDrawElements(GL_TRIANGLES, c->meshData.indices.size(), GL_UNSIGNED_INT, 0);
}
void WorldRenderer::Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
    worldShader->setMat4f("view", viewMatrix);
    worldShader->setMat4f("projection", projectionMatrix);

    for (Chunk *c : renderedChunks)
    {
        this->RenderChunck(c);
    }
}

WorldRenderer::~WorldRenderer()
{
    for (Chunk *c : renderedChunks)
    {
        delete c;
    }

    delete worldVertexBuffer;
    delete worldShader;
    delete worldTexture;
    delete cLoader;
}