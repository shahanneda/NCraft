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