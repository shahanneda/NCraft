#include "../world/Chunk.h"
#include "Buffer.h"
#include "Texture.h"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "Shader.h"

class WorldRenderer
{
public:
    WorldRenderer();
    ~WorldRenderer();
    void RenderChunck(Chunk *c);
    void Render(glm::mat4 projectionMatrix, glm::mat4 viewMatrix);
    vector<Chunk *> renderedChunks;

private:
    Shader *worldShader;
    VertexBuffer *worldVertexBuffer;
    Texture *worldTexture;
};