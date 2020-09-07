#include "WorldRenderer.h"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>
#include <algorithm>

using glm::vec2;
using glm::vec3;
WorldRenderer::WorldRenderer()
{
    worldVertexBuffer = new VertexBuffer();
    worldShader = new Shader("shaders/shader.vert", "shaders/shader.frag");
    worldTexture = new Texture("resources/texture_atlas.png");
    ;
}

void WorldRenderer::RenderChunck(Chunk *c)
{
    if (c->meshData.verts.size() == 0)
    { // dont have to render all air chunks
        return;
    }
    glActiveTexture(GL_TEXTURE0);
    worldTexture->BindTexture();
    worldShader->Bind();
    worldVertexBuffer->BindVertexArrayBuffer();
    worldVertexBuffer->PutVertexData(c->meshData.verts, c->meshData.indices, c->meshData.textureCoords, c->meshData.normals);

    glm::mat4 model = glm::mat4(1.0f); // model = local space to world space
    model = glm::translate(model, vec3(c->pos.x * Chunk::CHUNCK_SIZE, c->pos.y * Chunk::CHUNCK_SIZE, c->pos.z * Chunk::CHUNCK_SIZE));

    worldShader->setMat4f("model", model);
    glDrawElements(GL_TRIANGLES, c->meshData.indices.size(), GL_UNSIGNED_INT, 0);
}

void WorldRenderer::Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
    worldShader->setMat4f("view", viewMatrix);
    worldShader->setMat4f("projection", projectionMatrix);
    worldShader->setVec3f("lightColor", 1.0f, 0.0f, 0.0f);

    for (int i = 0; i < renderedChunks.size(); i++)
    {
        this->RenderChunck(renderedChunks[i]);
    }
}

void WorldRenderer::RemoveChunkFromRenderQueue(Chunk *c)
{
    std::vector<Chunk *>::iterator position = std::find(renderedChunks.begin(), renderedChunks.end(), c); // TODO: replace this with hash map lookup to speed this up by ALOT
    if (position != renderedChunks.end())
        renderedChunks.erase(position);
}

void WorldRenderer::AddChunkToRenderQueue(Chunk *c)
{
    renderedChunks.push_back(c);
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
}