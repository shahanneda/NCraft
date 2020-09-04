
#ifndef TERRAIN_GENERATOR
#define TERRAIN_GENERATOR
#include <FastNoise/FastNoise.h>
#include "Block.h"
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

class TerrainGenerator
{
public:
    TerrainGenerator();
    BLOCK_TYPE GetBlockTypeAtPos(glm::vec3 pos);

private:
    FastNoise *noise;
};
#endif