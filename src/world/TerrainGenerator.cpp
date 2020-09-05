#include "TerrainGenerator.h"
#include <iostream>

using glm::vec3;

TerrainGenerator::TerrainGenerator() : noise()
{
    noise.SetNoiseType(FastNoise::NoiseType::Perlin);
}

BLOCK_TYPE TerrainGenerator::GetBlockTypeAtPos(vec3 pos)
{

    int height = GetBlockHeightForPos(pos.x, pos.z);
    if (pos.y == height)
    {
        return GRASS;
    }
    if (pos.y < height)
    {
        return DIRT;
    }
    return AIR;
}

using std::pair;
// use memonization to speed up this function, as the noise call is very slow
int TerrainGenerator::GetBlockHeightForPos(float x, float z)
{
    int hash = HashOfTwoNumbers(x, z);
    auto mapIt = blockHeights.find(std::pair<int, int>(x, z));
    if (mapIt == blockHeights.end())
    {
        int blockHeight = (int)(maxBlockHeight * (float)noise.GetNoise(x * noiseScale, z * noiseScale));
        blockHeights.insert(std::pair<std::pair<int, int>, int>(std::pair<int, int>(x, z), blockHeight));
        return blockHeight;
    }
    return mapIt->second;
}

//  Cantor pairing function to hash two ints
int TerrainGenerator::HashOfTwoNumbers(int x, int y)
{
    return ((x + y) * (x + y + 1) / 2) + y;
}