#ifndef NCRAFT_WORLD
#define NCRAFT_WORLD
#include "../graphics/MasterRenderer.h"
#include "ChunkLoader.h"

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
};
#endif