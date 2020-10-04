
#ifndef TERRAIN_GENERATOR
#define TERRAIN_GENERATOR
#include <FastNoise/FastNoise.h>
#include "Block.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include <unordered_map>

enum BIOME{
    GRASSLAND,
    GRASSLAND_SAND,
    GRASSLAND_LAKE,
    DESERT,
    STONELAND,
};

class TerrainGenerator
{
public:
    TerrainGenerator();
    BLOCK_TYPE GetBlockTypeAtPos(glm::vec3 pos);
    BIOME GetBiomeForPos(int x, int y);
    float maxBlockHeight = 100;
    std::unordered_map<glm::vec2, int> blockHeights;
    std::unordered_map<glm::vec3, BLOCK_TYPE> treeBlocks;
    static int HashOfTwoNumbers(int x, int y);
    void GenerateTree(glm::vec3 pos);


private:
    FastNoise heightNoises;
    FastNoise biomeNoises;
    FastNoise treeNoise;
    int GetBlockHeightForPos(float x, float z);
    float noiseScaleHeight = 0.2f;
    float noiseScaleBiome = 0.1f;
};
#endif