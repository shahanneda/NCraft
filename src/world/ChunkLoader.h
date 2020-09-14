#ifndef CHUNK_LOADER
#define CHUNK_LOADER
// #include "../graphics/WorldRenderer.h"

#include <vector>
#include <unordered_map>
// #include <glm/gtx/hash.hpp>
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
    struct KeyHasher
    {
        std::size_t operator()(const glm::vec3& key) const
        {
            using std::size_t;
            using std::hash;
            // return ((key.x * 5209) * (key.y * 1811)) * (key.z * 7297);
            return key.x + key.y + key.z;
        }
    };

    // used to get specif blocks at world positions
    std::unordered_map<glm::vec3, Chunk *, KeyHasher> loadedChunks;

    std::vector<Chunk *> nonGeneratedChunks;
    std::vector<Chunk *> chunksToGenerate;

    TerrainGenerator *terrainGen;

    void NextChunkGenerationCycle(glm::vec3 playerPos);
    void PlayerMovedToNewChunk(glm::vec3 playerPos);
    void UpdateChunkAndNeighbers(Chunk *c);
    void UpdateChunk(Chunk *c);

    std::unordered_map<glm::vec3, Chunk*, KeyHasher> queueOfChunksToLoad;

    const float chunksRenderDistanceXZ = 4;
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
    void CheckIfNeighbersExistAndUpdate(Chunk *c);
    void GenerateChunks();
    void UnloadChunk(Chunk *c);
    void LoadChunk(Chunk *c);
};
#endif