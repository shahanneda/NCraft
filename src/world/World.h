#ifndef NCRAFT_WORLD
#define NCRAFT_WORLD
#include "../graphics/MasterRenderer.h"
#include "ChunkLoader.h"
#include "glm/glm.hpp"

class Camera;
class MasterRenderer;
class World
{
public:
    World(MasterRenderer *renderer, Camera *camera);
    ~World();
    MasterRenderer *renderer;
    ChunkLoader *cLoader;
    void GenerateChunks();
    void BreakBlock(glm::vec3 pos);
};
#endif