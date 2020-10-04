#include "TerrainGenerator.h"
#include <iostream>
#include <map>

using glm::vec3;

using std::pair;
std::map<BIOME, std::pair<float, float>> biomeRanges = {
    {GRASSLAND, pair<float, float>(0.0f, 80.0f)},
    {GRASSLAND_SAND, pair<float, float>(80.0f, 100.0f)},
    {DESERT, pair<float, float>(100.0f, 150.0f)},
    {STONELAND, pair<float, float>(150.0f, 200.0f)},
};

TerrainGenerator::TerrainGenerator() : heightNoises(),
                                       biomeNoises(), treeNoise()
{
    heightNoises.SetNoiseType(FastNoise::NoiseType::Perlin);
    biomeNoises.SetNoiseType(FastNoise::NoiseType::Simplex);
    treeNoise.SetNoiseType(FastNoise::NoiseType::Simplex);
}

BLOCK_TYPE TerrainGenerator::GetBlockTypeAtPos(vec3 pos)
{

    int height = GetBlockHeightForPos(pos.x, pos.z) + 100;
    // std::cout << height << std::endl;
    BIOME biome = GetBiomeForPos(pos.x, pos.z);
    if(pos.y == height + 1 && biome == GRASSLAND && treeNoise.GetNoise(pos.x*10, pos.z*10) > 0.95f){
        return WOOD;
    }

    if (pos.y == height)
    {
        switch (biome)
        {
        case GRASSLAND:
            return GRASS;
            break;
        case STONELAND:
            return STONE;
            break;
        case DESERT:
            return SAND;
            break;

        case GRASSLAND_SAND:
            return SAND;
            break;
        default:
            return GRASS;
            break;
        }
    }

    if (pos.y < height && pos.y > 30)
    {
        switch (biome)
        {
        case GRASSLAND:
            return DIRT;
            break;
        case STONELAND:
            return STONE;
            break;
        case DESERT:
            return SAND;
            break;

        case GRASSLAND_SAND:
            return DIRT;
            break;
        default:
            return GRASS;
            break;
        }
        return DIRT;
    }
    if (pos.y <= 30)
    {
        return STONE;
    }

    return AIR;
}

using std::pair;
// use memonization to speed up this function, as the noise call is very slow
int TerrainGenerator::GetBlockHeightForPos(float x, float z)
{
    // std::cout << "getting noie for x " << x << "  z  " << z << "  " << heightNoises.GetNoise(x*noiseScaleHeight,z*noiseScaleHeight)  << std::endl ;
    // int hash = HashOfTwoNumbers(x, z);
    // auto mapIt = blockHeights.find(glm::vec2(x, z));
    // if (mapIt == blockHeights.end())
    // {
        int blockHeight = (int)(maxBlockHeight * (float)heightNoises.GetNoise(x * noiseScaleHeight, z * noiseScaleHeight));
        // blockHeights.insert(std::pair<glm::vec2, int>(glm::vec2(x, z), blockHeight));
        return blockHeight;
    // }
    // return mapIt->second;
}

//  Cantor pairing function to hash two ints
int TerrainGenerator::HashOfTwoNumbers(int x, int y)
{
    return ((x + y) * (x + y + 1) / 2) + y;
}

BIOME TerrainGenerator::GetBiomeForPos(int x, int y)
{
    float noise = (biomeNoises.GetNoise(x * noiseScaleBiome, y * noiseScaleBiome) + 1.0f) * 100.0f;
    for (auto it = biomeRanges.begin(); it != biomeRanges.end(); ++it)
    {
        auto range = it->second; // this is a pair with two float like 100 - 150

        if (noise >= range.first && noise <= range.second)
        {
            return it->first;
        }
    }
    return BIOME::GRASSLAND;
}