#include "World.h"

World::World(MasterRenderer *renderer, Camera *camera)
{
    terrainGen = new TerrainGenerator();
    cLoader = new ChunkLoader(renderer->worldRenderer, terrainGen, camera);
    this->renderer = renderer;
    this->camera = camera;
}

World::~World()
{
    delete cLoader;
    delete terrainGen;
}

void World::GenerateChunks()
{
    cLoader->PlayerMovedToNewChunk(camera->position);
}

void World::Update(const float deltaTime, const double time)
{
    if (time > lastChunkGenTime + chunkGenerationUpdateInterval)
    {
        lastChunkGenTime = time;
        GenerateChunks();
    }
    cLoader->NextChunkGenerationCycle(camera->position);
}
void World::BreakBlock(glm::vec3 pos)
{

    Block *b = RayCastToNonAirBlock(pos, camera->target, 50.0f);
    std::cout << b->type << std::endl;
    std::cout << glm::to_string(b->position) << std::endl;

    b->type = AIR;
    b->isTransparent = true;

    cLoader->UpdateChunkAndNeighbers(b->chunk);
}

Block *World::RayCastToNonAirBlock(vec3 position, vec3 direction, float distance)
{
    Block *block = nullptr;
    for (float distanceGone = 0; distanceGone <= distance; distanceGone += raycastStep)
    {
        vec3 checkPos = position + (direction * distanceGone);
        block = cLoader->GetBlockAt(checkPos);
        if (block != nullptr && block->type != AIR)
        {
            break;
        }
    }

    return block;
}