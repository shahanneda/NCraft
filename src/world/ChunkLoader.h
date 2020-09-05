#ifndef CHUNK_LOADER
#define CHUNK_LOADER
// #include "../graphics/WorldRenderer.h"

#include <vector>
#include <unordered_map>
#include <glm/gtx/hash.hpp>
#include <glm/glm.hpp>

class WorldRenderer; // forward dec
class Chunk;         // forward dec
class TerrainGenerator;
namespace NCraft
{
    class Block;
}
class ChunkLoader
{
public:
    ChunkLoader(WorldRenderer *renderer, TerrainGenerator *terrainGen);
    ~ChunkLoader();

    // used to get specif blocks at world positions
    std::unordered_map<glm::vec3, Chunk *> loadedChunks;

    std::vector<Chunk *> nonGeneratedChunks;
    std::vector<Chunk *> chunksToGenerate;
    TerrainGenerator *terrainGen;

    void NextChunkGenerationCycle();
    void GenerateChunks();
    Chunk *GetChunkAtChunkPos(glm::vec3 pos);
    Chunk *GetChunkAtWorldPos(glm::vec3 pos);
    NCraft::Block *GetBlockAt(glm::vec3 pos);
    NCraft::Block *SetBlockAt(glm::vec3 pos);

    WorldRenderer *renderer;
};
#endif