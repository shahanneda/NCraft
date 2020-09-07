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
void World::BreakBlock()
{

    Block *b = RayCastToNonAirBlock(camera->position, camera->target, 50.0f);
    if (b == nullptr)
    {
        return;
    }
    std::cout << b->type << std::endl;
    std::cout << glm::to_string(b->position) << std::endl;

    b->type = AIR;
    b->isTransparent = true;

    cLoader->UpdateChunkAndNeighbers(b->chunk);
}
void World::PlaceBlock()
{

    Block *b = RayCastToNonAirBlock(camera->position, camera->target, 50.0f);
    if (b == nullptr)
    {
        return;
    }
    Block *airBesideB = RayCastToAirBlock(b->GetWorldPos(), -camera->target, 5.0f);
    if (airBesideB == nullptr)
    {
        return;
    }
    airBesideB->type = GRASS;
    airBesideB->isTransparent = false;

    cLoader->UpdateChunkAndNeighbers(airBesideB->chunk);
}

Block *World::RayCastToAirBlock(vec3 position, vec3 direction, float distance)
{
    Block *block = nullptr;
    for (float distanceGone = 0; distanceGone <= distance; distanceGone += raycastStep)
    {
        vec3 checkPos = position + (direction * distanceGone);
        block = cLoader->GetBlockAt(checkPos);
        if (block != nullptr && block->type == AIR && block->chunk->meshData.generated) // we dont want to return air, or a block that hasnt been generated yet
        {
            break;
        }
        else
        {
            block = nullptr;
        }
    }

    return block;
}
Block *World::RayCastToNonAirBlock(vec3 position, vec3 direction, float distance)
{
    Block *block = nullptr;
    for (float distanceGone = 0; distanceGone <= distance; distanceGone += raycastStep)
    {
        vec3 checkPos = position + (direction * distanceGone);
        block = cLoader->GetBlockAt(checkPos);
        if (block != nullptr && block->type != AIR && block->chunk->meshData.generated) // we dont want to return air, or a block that hasnt been generated yet
        {
            break;
        }
        else
        {
            block = nullptr;
        }
    }

    return block;
}