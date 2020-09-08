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
    std::cout << glGetError() << std::endl;
    worldVertexBuffer->PutVertexData(c->meshData.verts, c->meshData.indices, c->meshData.textureCoords, c->meshData.normals); // TODO: pass these by refrence or ptr instead of copy

    std::cout << glGetError() << std::endl;
    glm::mat4 model = glm::mat4(1.0f); // model = local space to world space
    model = glm::translate(model, vec3(c->pos.x * Chunk::CHUNCK_SIZE, c->pos.y * Chunk::CHUNCK_SIZE, c->pos.z * Chunk::CHUNCK_SIZE));

    std::cout << glGetError() << std::endl;
    worldShader->setMat4f("model", model);

    std::cout << glGetError() << std::endl;
    glDrawElements(GL_TRIANGLES, c->meshData.indices.size(), GL_UNSIGNED_INT, 0);

    std::cout << glGetError() << std::endl;
}

void WorldRenderer::Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
    std::cout << glGetError() << std::endl;
    glActiveTexture(GL_TEXTURE0);
    worldTexture->BindTexture();
    worldShader->Bind();
    worldVertexBuffer->BindVertexArrayBuffer();

    std::cout << glGetError() << std::endl;
    worldShader->setMat4f("view", viewMatrix);
    worldShader->setMat4f("projection", projectionMatrix);
    worldShader->setVec3f("lightColor", 0.9f, 0.9f, 0.9f);
    worldShader->setVec3f("lightPosition", 500.0f, 1000.0f, 500.0f);

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