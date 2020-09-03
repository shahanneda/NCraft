
#include "ChunkLoader.h"
#include "Chunk.h"
#include "glm/glm.hpp"
#include "../graphics/WorldRenderer.h"
using glm::vec3;
using std::vector;

ChunkLoader::ChunkLoader(WorldRenderer *renderer) : loadedChunks()
{
    this->renderer = renderer;
    Chunk *mainChunk = new Chunk(vec3(0, 0, 0));
    loadedChunks.push_back(mainChunk);
}

void ChunkLoader::NextChunkGenerationCycle()
{
    std::cout << "generating chunks" << std::endl;
    int lengthOfLoadedChunksAtStart = loadedChunks.size();
    for (int i = 0; i < lengthOfLoadedChunksAtStart; i++)
    {
        Chunk *c = loadedChunks[i];
        if (c->positiveXNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x + 1, c->pos.y, c->pos.z));
            c->positiveXNeighber = newChunk;
            loadedChunks.push_back(newChunk);
            newChunk->negativeXNeighber = c;
        }
        if (c->negativeXNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x - 1, c->pos.y, c->pos.z));
            c->negativeXNeighber = newChunk;
            loadedChunks.push_back(newChunk);
            newChunk->positiveXNeighber = c;
        }

        if (c->positiveYNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x, c->pos.y + 1, c->pos.z));
            c->positiveYNeighber = newChunk;
            loadedChunks.push_back(newChunk);
            newChunk->negativeYNeighber = c;
        }
        if (c->negativeYNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x, c->pos.y - 1, c->pos.z));
            c->negativeYNeighber = newChunk;
            loadedChunks.push_back(newChunk);
            newChunk->positiveYNeighber = c;
        }

        if (c->positiveZNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x, c->pos.y, c->pos.z + 1));
            c->positiveZNeighber = newChunk;
            loadedChunks.push_back(newChunk);
            newChunk->negativeZNeighber = c;
        }
        if (c->negativeZNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x, c->pos.y, c->pos.z - 1));
            c->negativeZNeighber = newChunk;
            loadedChunks.push_back(newChunk);
            newChunk->positiveZNeighber = c;
        }

        if (c->hasAllNeighbers() && !c->meshData.generated)
        {
            c->meshData.GenerateData();
            renderer->renderedChunks.push_back(c);
        }
    }

    // mainChunk->meshData.GenerateData();
}
ChunkLoader::~ChunkLoader()
{
    for (Chunk *c : loadedChunks)
    {
        delete c;
    }
}
