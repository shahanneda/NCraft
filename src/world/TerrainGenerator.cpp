#include "TerrainGenerator.h"
#include <iostream>

using glm::vec3;

TerrainGenerator::TerrainGenerator() : noise()
{
    noise.SetNoiseType(FastNoise::NoiseType::Simplex);
}

BLOCK_TYPE TerrainGenerator::GetBlockTypeAtPos(vec3 pos)
{

    int height = GetBlockHeightForPos(pos.x, pos.z) + 50;
    if (pos.y == height)
    {
        return SAND;
    }
    if (pos.y < height && pos.y > 50)
    {
        return DIRT;
    }
    if(pos.y <= 50){
        return STONE;
    }

    return AIR;
}

using std::pair;
// use memonization to speed up this function, as the noise call is very slow
int TerrainGenerator::GetBlockHeightForPos(float x, float z)
{
    int hash = HashOfTwoNumbers(x, z);
    auto mapIt = blockHeights.find(glm::vec2(x, z));
    if (mapIt == blockHeights.end())
    {
        int blockHeight = (int)(maxBlockHeight * (float)noise.GetNoise(x * noiseScale, z * noiseScale));
        blockHeights.insert(std::pair<glm::vec2, int>(glm::vec2(x, z), blockHeight));
        return blockHeight;
    }
    return mapIt->second;
}

//  Cantor pairing function to hash two ints
int TerrainGenerator::HashOfTwoNumbers(int x, int y)
{
    return ((x + y) * (x + y + 1) / 2) + y;
}