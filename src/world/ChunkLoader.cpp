
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

ChunkLoader::ChunkLoader(WorldRenderer *renderer, TerrainGenerator *terrainGen, Camera *camera) : loadedChunks()
{
    this->renderer = renderer;
    this->terrainGen = terrainGen;
    this->camera = camera;
    Chunk *mainChunk = new Chunk(vec3(0, 0, 0), terrainGen);
    loadedChunks.insert(std::pair<glm::vec3, Chunk *>(mainChunk->pos, mainChunk));
    nonGeneratedChunks.push_back(mainChunk);
}

Chunk *ChunkLoader::GetChunkAtChunkPos(vec3 pos)
{
    auto cIter = loadedChunks.find(pos);
    if (cIter == loadedChunks.end())
    {
        // std::cout << "Trying to get Chunk that is not loaded!!!" << glm::to_string(pos) << std::endl;
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

// this is the core of the chunkloaidng, it checks in a increment around the player and adds those chunks to a queue
void ChunkLoader::PlayerMovedToNewChunk(vec3 playerPos)
{
    vec3 playerChunkPos = GetChunkPositionFromWorldPosition(playerPos);
    for (int xInc = -chunksRenderDistanceXZ; xInc < chunksRenderDistanceXZ; xInc++)
    {
        for (int zInc = -chunksRenderDistanceXZ; zInc < chunksRenderDistanceXZ; zInc++)
        {
            for (int yInc = -chunksRenderDistanceY; yInc < chunksRenderDistanceY; yInc++)
            {
                vec3 newChunkPosition = vec3(playerChunkPos.x + xInc, playerChunkPos.y + yInc, playerChunkPos.z + zInc);
                Chunk *chunkNearPlayer = GetChunkAtChunkPos(newChunkPosition);
                if (chunkNearPlayer == nullptr) // first check if it doesnt exits
                {
                    chunkNearPlayer = new Chunk(newChunkPosition, terrainGen);
                    loadedChunks.insert(std::pair<vec3, Chunk *>(chunkNearPlayer->pos, chunkNearPlayer));
                }
                if (!chunkNearPlayer->meshData.generated && !chunkNearPlayer->inQueueToBeGenerated) // now we check maybe it exists but just hasnt been generated yet, and if it is already in the queue(so we dont add it again)
                {
                    chunkNearPlayer->inQueueToBeGenerated = true;
                    this->queueOfChunksToLoad.push(chunkNearPlayer);
                    std::cout << queueOfChunksToLoad.size() << std::endl;
                }
            }
        }
    }

    // Check and unload any chuncks far away
    for (auto it = loadedChunks.begin(); it != loadedChunks.end();)
    {
        Chunk *c = it->second;
        if (ShouldUnloadChunk(c, playerPos))
        {
            it = loadedChunks.erase(it);
            UnloadChunk(c);
        }
        else
        {
            ++it;
        }
    }
}

bool ChunkLoader::ShouldUnloadChunk(Chunk *c, glm::vec3 playerPos)
{
    float distance = glm::distance(GetChunkPositionFromWorldPosition(playerPos), c->pos);

    return distance - 2 > chunksRenderDistanceXZ;
}

void ChunkLoader::UnloadChunk(Chunk *c) // remove all the neighbers from the render queue, and add them to non generated chunks, and reset their neighbers
{
    renderer->RemoveChunkFromRenderQueue(c);
    loadedChunks.erase(c->pos);

    renderer->RemoveChunkFromRenderQueue(c->positiveXNeighber);
    if (c->positiveXNeighber)
    {
        c->positiveXNeighber->negativeXNeighber = nullptr;
    }

    renderer->RemoveChunkFromRenderQueue(c->negativeXNeighber);
    if (c->negativeXNeighber)
    {
        c->negativeXNeighber->positiveXNeighber = nullptr;
    }

    renderer->RemoveChunkFromRenderQueue(c->positiveYNeighber);
    if (c->positiveYNeighber)
    {
        c->positiveYNeighber->negativeYNeighber = nullptr;
    }

    renderer->RemoveChunkFromRenderQueue(c->negativeYNeighber);
    if (c->negativeYNeighber)
    {
        c->negativeYNeighber->positiveYNeighber = nullptr;
    }

    renderer->RemoveChunkFromRenderQueue(c->positiveZNeighber);
    if (c->positiveZNeighber)
    {
        c->positiveZNeighber->negativeZNeighber = nullptr;
    }

    renderer->RemoveChunkFromRenderQueue(c->negativeZNeighber);
    if (c->negativeZNeighber)
    {
        c->negativeZNeighber->positiveZNeighber = nullptr;
    }

    delete c;
}

void ChunkLoader::LoadChunk(Chunk *c)
{

    vector<Chunk *> newNonGeneratedChunks; // store it here for temp, since we dont want the size of it actuallly changing
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
        chunksToGenerate.push_back(c); // it it to list so we can generate on another thread
    }

    loadedChunks.insert(pair<vec3, Chunk *>(c->pos, c));
    nonGeneratedChunks.insert(nonGeneratedChunks.end(), newNonGeneratedChunks.begin(), newNonGeneratedChunks.end()); // add the new chuncks to the  non generated chunks
    GenerateChunks();
    // std::thread t(&ChunkLoader::GenerateChunks, this);
    // t.detach();
}

void ChunkLoader::NextChunkGenerationCycle(vec3 playerPos)
{
    if (loadedChunks.size() > 1000)
    {
        return;
    }

    if (!queueOfChunksToLoad.empty())
    {
        Chunk *c = queueOfChunksToLoad.front();
        queueOfChunksToLoad.pop();
        if (!ShouldUnloadChunk(c, camera->position)) // if a chunk is out of range, dont bother loading it
        {
            LoadChunk(c);
        }
        else
        {
            UnloadChunk(c);
        }
    }

    nonGeneratedChunks.clear();
}
void ChunkLoader::GenerateChunks()
{
    for (int i = 0; i < chunksToGenerate.size(); i++)
    {
        Chunk *chunk = chunksToGenerate[i];
        if (chunk->hasAllNeighbers()) // check if for somereason it doesnt have all its neghbers
        {
            chunk->meshData.GenerateData();
            renderer->AddChunkToRenderQueue(chunk); // possibly move this to the other thread??
        }
        else
        {
            chunksToGenerate.erase(chunksToGenerate.begin() + i);
        }
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
