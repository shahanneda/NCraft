#ifndef WORLD_RENDERER
#define WORLD_RENDERER
#include "../world/Chunk.h"
#include "Buffer.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Shader.h"
#include "../world/ChunkLoader.h"
#include <memory>

class WorldRenderer
{
public:
    WorldRenderer();
    ~WorldRenderer();
    void RenderChunck(Chunk *c);
    void Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
    void AddChunkToRenderQueue(Chunk *c);
    void RemoveChunkFromRenderQueue(Chunk *c);

private:
    vector<Chunk *> renderedChunks; // replace this with hash map so we can delete and get easier
    Shader *worldShader;
    VertexBuffer *worldVertexBuffer;
    Texture *worldTexture;
};
#endif