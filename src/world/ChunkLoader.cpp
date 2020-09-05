
#include <algorithm>
#include "ChunkLoader.h"
#include "Chunk.h"
#include "../graphics/WorldRenderer.h"
#include <iterator>
#include <glm/gtx/string_cast.hpp>
#include <thread>

using glm::vec3;
using std::floor;
using std::pair;
using std::vector;

ChunkLoader::ChunkLoader(WorldRenderer *renderer, TerrainGenerator *terrainGen) : loadedChunks()
{
    this->renderer = renderer;
    this->terrainGen = terrainGen;
    Chunk *mainChunk = new Chunk(vec3(0, 0, 0), terrainGen);
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
    vec3 chunkPos = GetChunkPositionFromWorldPosition(pos);
    Chunk *c = GetChunkAtChunkPos(chunkPos);
    // std::cout << "got chunk at chunk pos " <<
    return c;
}

glm::vec3 ChunkLoader::GetChunkPositionFromWorldPosition(glm::vec3 pos)
{
    return vec3((int)floor(pos.x / Chunk::CHUNCK_SIZE), (int)floor(pos.y / Chunk::CHUNCK_SIZE), (int)floor(pos.z / Chunk::CHUNCK_SIZE));
}

NCraft::Block *ChunkLoader::GetBlockAt(vec3 pos)
{
    std::cout << "getting block at" << glm::to_string(pos) << std::endl;
    Chunk *c = GetChunkAtWorldPos(pos);
    if (c)
    {
        Block *k = c->GetBlockAt(vec3((int)floor(pos.x - c->pos.x * Chunk::CHUNCK_SIZE), (int)floor(pos.y - c->pos.y * Chunk::CHUNCK_SIZE), (int)floor(pos.z - c->pos.z * Chunk::CHUNCK_SIZE)));
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

// two stages of removal of chunks, first if its distance is longer than the render distace, remove it form the rendere queue (loaded but not rendred)
// secondly if its distance is very far away, renderDistance*2 , then we can can delte the chunk, by removing all neighbers from render queue, and then deleting this chunk

void ChunkLoader::PlayerMovedToNewChunk(vec3 playerPos)
{

    // if (GetChunkAtWorldPos(playerPos) == nullptr)
    // {
    //     Chunk *newChunk = new Chunk(GetChunkPositionFromWorldPosition(playerPos), terrainGen);
    //     loadedChunks.insert(std::pair<glm::vec3, Chunk *>(newChunk->pos, newChunk));
    //     nonGeneratedChunks.push_back(newChunk);
    // }
    // for (auto it = loadedChunks.begin(); it != loadedChunks.end();)
    // {
    //     Chunk *c = it->second;
    //     float distance = glm::distance(playerPos, c->GetWorldPos());
    //     if (distance > renderDistance)
    //     {
    //         loadedChunks.erase(it++); // this erases in a way that doesnt kill the it
    //         UnloadChunk(c);
    //     }
    //     else
    //     {
    //         ++it;
    //     }
    // }
    // NextChunkGenerationCycle();
}
void ChunkLoader::UnloadChunk(Chunk *c) // remove all the neighbers from the render queue, and add them to non generated chunks
{
    renderer->RemoveChunkFromRenderQueue(c);

    renderer->RemoveChunkFromRenderQueue(c->positiveXNeighber);
    nonGeneratedChunks.push_back(c->positiveXNeighber);

    renderer->RemoveChunkFromRenderQueue(c->negativeXNeighber);
    nonGeneratedChunks.push_back(c->negativeXNeighber);

    renderer->RemoveChunkFromRenderQueue(c->positiveYNeighber);
    nonGeneratedChunks.push_back(c->positiveYNeighber);

    renderer->RemoveChunkFromRenderQueue(c->negativeYNeighber);
    nonGeneratedChunks.push_back(c->negativeYNeighber);

    renderer->RemoveChunkFromRenderQueue(c->positiveZNeighber);
    nonGeneratedChunks.push_back(c->positiveZNeighber);

    renderer->RemoveChunkFromRenderQueue(c->negativeZNeighber);
    nonGeneratedChunks.push_back(c->negativeZNeighber);

    delete c;
}
void ChunkLoader::NextChunkGenerationCycle()
{
    if (loadedChunks.size() > 1000)
    {
        return;
    }
    std::cout << "generating chunks" << std::endl;
    vector<Chunk *> newNonGeneratedChunks; // store it here for temp, since we dont want the size of it actuallly changing
    for (auto it = nonGeneratedChunks.begin(); it != nonGeneratedChunks.end();)
    {
        Chunk *c = *it;
        // Chunk *c = nonGeneratedChunks.back();
        // nonGeneratedChunks.pop_back();
        if (c->positiveXNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x + 1, c->pos.y, c->pos.z), terrainGen);
            c->positiveXNeighber = newChunk;
            loadedChunks.insert(pair<vec3, Chunk *>(newChunk->pos, newChunk));
            newNonGeneratedChunks.push_back(newChunk);
            newChunk->negativeXNeighber = c;
        }
        if (c->negativeXNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x - 1, c->pos.y, c->pos.z), terrainGen);
            c->negativeXNeighber = newChunk;
            loadedChunks.insert(pair<vec3, Chunk *>(newChunk->pos, newChunk));
            newNonGeneratedChunks.push_back(newChunk);
            newChunk->positiveXNeighber = c;
        }

        if (c->positiveYNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x, c->pos.y + 1, c->pos.z), terrainGen);
            c->positiveYNeighber = newChunk;
            loadedChunks.insert(pair<vec3, Chunk *>(newChunk->pos, newChunk));
            newNonGeneratedChunks.push_back(newChunk);
            newChunk->negativeYNeighber = c;
        }
        if (c->negativeYNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x, c->pos.y - 1, c->pos.z), terrainGen);
            c->negativeYNeighber = newChunk;
            loadedChunks.insert(pair<vec3, Chunk *>(newChunk->pos, newChunk));
            newNonGeneratedChunks.push_back(newChunk);
            newChunk->positiveYNeighber = c;
        }

        if (c->positiveZNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x, c->pos.y, c->pos.z + 1), terrainGen);
            c->positiveZNeighber = newChunk;
            loadedChunks.insert(pair<vec3, Chunk *>(newChunk->pos, newChunk));
            newNonGeneratedChunks.push_back(newChunk);
            newChunk->negativeZNeighber = c;
        }
        if (c->negativeZNeighber == nullptr)
        {
            Chunk *newChunk = new Chunk(vec3(c->pos.x, c->pos.y, c->pos.z - 1), terrainGen);
            c->negativeZNeighber = newChunk;
            loadedChunks.insert(pair<vec3, Chunk *>(newChunk->pos, newChunk));
            newNonGeneratedChunks.push_back(newChunk);
            newChunk->positiveZNeighber = c;
        }

        if (c->hasAllNeighbers() && !c->meshData.generated) // if this chunk is ready to be generated
        {
            it = nonGeneratedChunks.erase(it); // remove in a way that doesnt mess up the iterator
            chunksToGenerate.push_back(c);     // it it to list so we can generate on another thread
        }
        else
        {
            ++it;
        }
    }

    nonGeneratedChunks.insert(nonGeneratedChunks.end(), newNonGeneratedChunks.begin(), newNonGeneratedChunks.end()); // add the new chuncks to the  non generated chunks
    std::thread t(&ChunkLoader::GenerateChunks, this);
    t.detach();
}
void ChunkLoader::GenerateChunks()
{
    for (int i = 0; i < chunksToGenerate.size(); i++)
    {
        Chunk *chunk = chunksToGenerate[i];
        chunk->meshData.GenerateData();
        renderer->AddChunkToRenderQueue(chunk); // possibly move this to the other thread??
    }
    chunksToGenerate.clear();
}
ChunkLoader::~ChunkLoader()
{
    for (auto it = loadedChunks.begin(); it != loadedChunks.end(); ++it)
    {
        delete it->second;
    }
}
