
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
    float maxBlockHeight = 100;

private:
    FastNoise noise;
    int GetBlockHeightForPos(float x, float z);
    float noiseScale = 0.5f;
};
#endif