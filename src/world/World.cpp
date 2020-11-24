#include "World.h"

using glm::floor;
World::World(MasterRenderer *renderer, Player *player)
{
    terrainGen = new TerrainGenerator();
    cLoader = new ChunkLoader(renderer->worldRenderer, terrainGen, &player->camera);
    this->renderer = renderer;
    this->player = player;
}

World::~World()
{
    delete cLoader;
    delete terrainGen;
}

void World::GenerateChunks()
{
    cLoader->PlayerMovedToNewChunk(player->camera.position);
}

void World::Update(const float deltaTime, const double time)
{
    if (time > lastChunkGenTime + chunkGenerationUpdateInterval)
    {
        lastChunkGenTime = time;
        GenerateChunks();
    }
    cLoader->NextChunkGenerationCycle(player->camera.position);
}
void World::BreakBlock()
{

    Block *b = RayCastToNonAirBlock(player->camera.position, player->camera.target, 50.0f, nullptr);
    if (b == nullptr)
    {
        return;
    }

    b->type = AIR;
    b->isTransparent = true;

    cLoader->UpdateChunkAndNeighbers(b->chunk);
}
void World::PlaceBlock()
{
    vec3 faceEntered(0, 0, 0);
    Block *b = RayCastToNonAirBlock(player->camera.position, player->camera.target, 50.0f, &faceEntered);
    if (b == nullptr)
    {
        return;
    }
    Block *airBesideB = RayCastToAirBlock(b->GetWorldPos(), faceEntered, 5.0f);
    if (airBesideB == nullptr)
    {
        return;
    }
    airBesideB->type = player->currentBlockTypeSelected;
    airBesideB->isTransparent = false;

    cLoader->UpdateChunkAndNeighbers(airBesideB->chunk);
}

Block *World::GetBlock(vec3 position){
    return cLoader->GetBlockAt(position);
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
Block *World::RayCastToNonAirBlock(vec3 position, vec3 direction, float distance, vec3 *outFaceNormal)
{
    vec3 lastFace(0, 0, 0);
    Block *block = nullptr;
    for (float distanceGone = 0; distanceGone <= distance; distanceGone += raycastStep)
    {
        vec3 checkPos = position + (direction * distanceGone);

        // this is for checking what face we entered from, we floor to detect diffrences like 6.999 to 7.000, so it wil become obvious what face it is since if we do 7-6 we get 1, so we know thats the face we entered in.
        vec3 flooredCheckPos = vec3(floor(checkPos.x), floor(checkPos.y), floor(checkPos.z));
        vec3 faceDirection = lastFace - flooredCheckPos;
        lastFace = flooredCheckPos;

        block = cLoader->GetBlockAt(checkPos);
        if (block != nullptr && block->type != AIR && block->chunk->meshData.generated) // we dont want to return air, or a block that hasnt been generated yet
        {
            if (outFaceNormal != nullptr)
            {
                outFaceNormal->x = faceDirection.x;
                outFaceNormal->y = faceDirection.y;
                outFaceNormal->z = faceDirection.z;
            }

            break;
        }
        else
        {
            block = nullptr;
        }
    }

    return block;
}