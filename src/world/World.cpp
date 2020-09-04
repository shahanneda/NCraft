#include "World.h"

World::World(MasterRenderer *renderer, Camera *camera)
{
    cLoader = new ChunkLoader(renderer->worldRenderer);
    this->renderer = renderer;
}

World::~World()
{
    delete cLoader;
}

void World::GenerateChunks()
{
    cLoader->NextChunkGenerationCycle();
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