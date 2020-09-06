#ifndef CHUNK_LOADER
#define CHUNK_LOADER
// #include "../graphics/WorldRenderer.h"

#include <vector>
#include <unordered_map>
#include <glm/gtx/hash.hpp>
#include <glm/glm.hpp>
#include <queue>
#include "../graphics/Camera.h"
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
    ChunkLoader(WorldRenderer *renderer, TerrainGenerator *terrainGen, Camera *camera);
    ~ChunkLoader();

    // used to get specif blocks at world positions
    std::unordered_map<glm::vec3, Chunk *> loadedChunks;

    std::vector<Chunk *> nonGeneratedChunks;
    std::vector<Chunk *> chunksToGenerate;
    TerrainGenerator *terrainGen;

    void NextChunkGenerationCycle(glm::vec3 playerPos);
    void PlayerMovedToNewChunk(glm::vec3 playerPos);
    void GenerateChunks();
    void UnloadChunk(Chunk *c);
    void LoadChunk(Chunk *c);

    std::queue<Chunk *> queueOfChunksToLoad;
    const float chunksRenderDistanceXZ = 2;
    const float chunksUnloadDistanceInBlocks = 100.0f;
    ;
    const float chunksRenderDistanceY = 2;

    glm::vec3 GetChunkPositionFromWorldPosition(glm::vec3 pos);
    Chunk *GetChunkAtChunkPos(glm::vec3 pos);
    Chunk *GetChunkAtWorldPos(glm::vec3 pos);
    NCraft::Block *GetBlockAt(glm::vec3 pos);
    NCraft::Block *SetBlockAt(glm::vec3 pos);

    WorldRenderer *renderer;

private:
    Camera *camera;
    bool ShouldUnloadChunk(Chunk *, glm::vec3 playerPos);
};
#endif