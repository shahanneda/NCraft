#ifndef NCRAFT_WORLD
#define NCRAFT_WORLD
#include "../graphics/MasterRenderer.h"
#include "ChunkLoader.h"
#include "glm/glm.hpp"
#include "TerrainGenerator.h"

class Camera;
class MasterRenderer;
class World
{
public:
    World(MasterRenderer *renderer, Camera *camera);
    ~World();
    MasterRenderer *renderer;
    TerrainGenerator *terrainGen;
    ChunkLoader *cLoader;
    Camera *camera;
    void Update();
    void GenerateChunks();
    void BreakBlock(glm::vec3 pos);
};
#endif