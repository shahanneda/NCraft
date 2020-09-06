#include "World.h"

World::World(MasterRenderer *renderer, Camera *camera)
{
    terrainGen = new TerrainGenerator();
    cLoader = new ChunkLoader(renderer->worldRenderer, terrainGen);
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
    // cLoader->PlayerMovedToNewChunk(camera->position);
}

void World::Update()
{
    cLoader->NextChunkGenerationCycle(camera->position);
    // cLoader->NextChunkGenerationCycle();
}
void World::BreakBlock(glm::vec3 pos)
{
    std::cout << "broke blokc" << std::endl;
    cLoader->GetBlockAt(pos)->type = AIR;
    cLoader->GetBlockAt(pos)->isTransparent = true;
    Chunk *c = cLoader->GetChunkAtWorldPos(pos);
    c->meshData.verts.clear();
    c->meshData.indices.clear();
    c->meshData.textureCoords.clear();
    c->meshData.GenerateData();
}