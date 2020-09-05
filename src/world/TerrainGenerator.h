
#ifndef TERRAIN_GENERATOR
#define TERRAIN_GENERATOR
#include <FastNoise/FastNoise.h>
#include "Block.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <unordered_map>

class TerrainGenerator
{
public:
    TerrainGenerator();
    BLOCK_TYPE GetBlockTypeAtPos(glm::vec3 pos);
    float maxBlockHeight = 100;
    std::unordered_map<glm::vec2, int> blockHeights;
    static int HashOfTwoNumbers(int x, int y);

private:
    FastNoise noise;
    int GetBlockHeightForPos(float x, float z);
    float noiseScale = 0.5f;
};
#endif