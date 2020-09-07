#ifndef NCRAFT_WORLD
#define NCRAFT_WORLD
#include "../graphics/MasterRenderer.h"
#include "ChunkLoader.h"
#include "glm/glm.hpp"
#include "TerrainGenerator.h"

class Camera;
class MasterRenderer;

using namespace NCraft;
using glm::vec3;

class World
{
public:
    World(MasterRenderer *renderer, Camera *camera);
    ~World();
    MasterRenderer *renderer;
    TerrainGenerator *terrainGen;
    ChunkLoader *cLoader;
    Camera *camera;

    void Update(const float, const double);
    void GenerateChunks();
    void BreakBlock();
    void PlaceBlock();
    Block *RayCastToNonAirBlock(vec3 position, vec3 direction, float distance);
    Block *RayCastToAirBlock(vec3 position, vec3 direction, float distance);

private:
    double chunkGenerationUpdateInterval = 1.0;
    double lastChunkGenTime = 0;
    float raycastStep = 0.1f;
};
#endif