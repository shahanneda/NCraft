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

int TerrainGenerator::GetBlockHeightForPos(float x, float z)
{
    // TODO: check if we shoudl cache this value -- memonising
    int blockHeight = (int)(maxBlockHeight * (float)noise.GetNoise(x * noiseScale, z * noiseScale));
    return blockHeight;
}
