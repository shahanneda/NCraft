#ifndef CHUNK_LOADER
#define CHUNK_LOADER
// #include "../graphics/WorldRenderer.h"

#include <vector>
class WorldRenderer; // forward dec
class Chunk;         // forward dec
class ChunkLoader
{
public:
    ChunkLoader(WorldRenderer *renderer);
    std::vector<Chunk *> loadedChunks;
    void NextChunkGenerationCycle();
    ~ChunkLoader();

    WorldRenderer *renderer;
};
#endif