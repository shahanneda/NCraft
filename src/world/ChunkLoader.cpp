
#include <algorithm>
#include "ChunkLoader.h"
#include "Chunk.h"
#include "../graphics/WorldRenderer.h"
#include <iterator>
#include <glm/gtx/string_cast.hpp>

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

Chunk *ChunkLoader::GetChunkAtChunkPos(vec3 pos)
{
    auto cIter = loadedChunks.find(pos);
    if (cIter == loadedChunks.end())
    {
        std::cout << "Trying to get Chunk that is not loaded!!!" << glm::to_string(pos) << std::endl;
        return nullptr;
    }
    return cIter->second;
};

Chunk *ChunkLoader::GetChunkAtWorldPos(glm::vec3 pos)
{
    vec3 chunkPos = vec3((int)pos.x / Chunk::CHUNCK_SIZE, (int)pos.y / Chunk::CHUNCK_SIZE, (int)pos.z / Chunk::CHUNCK_SIZE);
    Chunk *c = GetChunkAtChunkPos(chunkPos);
    // std::cout << "got chunk at chunk pos " <<
}
NCraft::Block *ChunkLoader::GetBlockAt(vec3 pos)
{
    std::cout << "getting block at" << glm::to_string(pos) << std::endl;
    Chunk *c = GetChunkAtWorldPos(pos);
    if (c)
    {
        Block *k = c->GetBlockAt(vec3(pos.x - c->pos.x * Chunk::CHUNCK_SIZE, pos.y - c->pos.y * Chunk::CHUNCK_SIZE, pos.z - c->pos.z * Chunk::CHUNCK_SIZE));
        if (!k)
        {
            std::cout << "BLOCK NOT FOUND " << std::endl;
            return nullptr;
        }
        std::cout << "got block" << glm::to_string(k->position) << std::endl;
        return k;
    }
    return nullptr;
}

NCraft::Block *ChunkLoader::SetBlockAt(vec3 pos)
{
    // Chunk *c = GetChunkAtWorldPos(pos);
    // if (c)
    // {
    //     return c->GetBlockAt(vec3(pos.x - c->pos.x, pos.y - c->pos.y, pos.z - c->pos.z));
    // }
    return nullptr;
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
