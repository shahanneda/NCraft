#ifndef CHUNK_LOADER
#define CHUNK_LOADER
// #include "../graphics/WorldRenderer.h"

#include <vector>
#include <unordered_map>
#include <glm/gtx/hash.hpp>
#include <glm/glm.hpp>
class WorldRenderer; // forward dec
class Chunk;         // forward dec
class ChunkLoader
{
public:
    ChunkLoader(WorldRenderer *renderer);
    std::unordered_map<glm::vec3, Chunk *> loadedChunks;
    std::vector<Chunk*> nonGeneratedChunks;
    void NextChunkGenerationCycle();
    ~ChunkLoader();

    WorldRenderer *renderer;
};
#endif