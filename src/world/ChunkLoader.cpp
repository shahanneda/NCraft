
#include <algorithm>
#include "ChunkLoader.h"
#include "Chunk.h"
#include "../graphics/WorldRenderer.h"
#include <iterator>

using glm::vec3;
using std::pair;
using std::vector;

ChunkLoader::ChunkLoader(WorldRenderer *renderer) : loadedChunks()
{
    this->renderer = renderer;
    Chunk *mainChunk = new Chunk(vec3(0, 0, 0));
    loadedChunks.insert(std::pair<glm::vec3, Chunk *>(mainChunk->pos, mainChunk));
    nonGeneratedChunks.push_back(mainChunk);
}

void ChunkLoader::NextChunkGenerationCycle()
{
    std::cout << "generating chunks" << std::endl;
    vector<Chunk *> newNonGeneratedChunks; // store it here for temp, since we dont want the size of it actuallly changing
    for (auto it = nonGeneratedChunks.begin(); it != nonGeneratedChunks.end();)
    {
        Chunk *c = *it;
        if (c->positiveXNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x + 1, c->pos.y, c->pos.z));
            c->positiveXNeighber = newChunk;
            loadedChunks.insert(pair<vec3, Chunk *>(newChunk->pos, newChunk));
            newNonGeneratedChunks.push_back(newChunk);
            newChunk->negativeXNeighber = c;
        }
        if (c->negativeXNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x - 1, c->pos.y, c->pos.z));
            c->negativeXNeighber = newChunk;
            loadedChunks.insert(pair<vec3, Chunk *>(newChunk->pos, newChunk));
            newNonGeneratedChunks.push_back(newChunk);
            newChunk->positiveXNeighber = c;
        }

        if (c->positiveYNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x, c->pos.y + 1, c->pos.z));
            c->positiveYNeighber = newChunk;
            loadedChunks.insert(pair<vec3, Chunk *>(newChunk->pos, newChunk));
            newNonGeneratedChunks.push_back(newChunk);
            newChunk->negativeYNeighber = c;
        }
        if (c->negativeYNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x, c->pos.y - 1, c->pos.z));
            c->negativeYNeighber = newChunk;
            loadedChunks.insert(pair<vec3, Chunk *>(newChunk->pos, newChunk));
            newNonGeneratedChunks.push_back(newChunk);
            newChunk->positiveYNeighber = c;
        }

        if (c->positiveZNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x, c->pos.y, c->pos.z + 1));
            c->positiveZNeighber = newChunk;
            loadedChunks.insert(pair<vec3, Chunk *>(newChunk->pos, newChunk));
            newNonGeneratedChunks.push_back(newChunk);
            newChunk->negativeZNeighber = c;
        }
        if (c->negativeZNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x, c->pos.y, c->pos.z - 1));
            c->negativeZNeighber = newChunk;
            loadedChunks.insert(pair<vec3, Chunk *>(newChunk->pos, newChunk));
            newNonGeneratedChunks.push_back(newChunk);
            newChunk->positiveZNeighber = c;
        }

        if (c->hasAllNeighbers() && !c->meshData.generated)
        {
            it = nonGeneratedChunks.erase(it); // remove in a way that doesnt mess up the iterator
            c->meshData.GenerateData();
            renderer->renderedChunks.push_back(c);
        }
        else
        {
            ++it;
        }
    }

    nonGeneratedChunks.insert(nonGeneratedChunks.end(), newNonGeneratedChunks.begin(), newNonGeneratedChunks.end()); // add the new chuncks to the  non generated chunks
    // mainChunk->meshData.GenerateData();
}
ChunkLoader::~ChunkLoader()
{
    for (auto it = loadedChunks.begin(); it != loadedChunks.end(); ++it)
    {
        delete it->second;
    }
}
