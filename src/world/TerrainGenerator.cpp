#include "TerrainGenerator.h"
#include <iostream>
#include <map>
#include <stdlib.h>

using glm::vec3;

using std::pair;
std::map<BIOME, std::pair<float, float>> biomeRanges = {
    {GRASSLAND, pair<float, float>(0.0f, 99.0f)},
    {GRASSLAND_SAND, pair<float, float>(99.0f, 100.0f)},
    {DESERT, pair<float, float>(100.0f, 150.0f)},
    {STONELAND, pair<float, float>(150.0f, 200.0f)},
};

TerrainGenerator::TerrainGenerator() : heightNoises(),
                                       biomeNoises(), treeNoise()
{
    heightNoises.SetNoiseType(FastNoise::NoiseType::Perlin);
    biomeNoises.SetNoiseType(FastNoise::NoiseType::Simplex);
    treeNoise.SetNoiseType(FastNoise::NoiseType::Simplex);
    biomeNoises.SetSeed(4594);
    srand((unsigned) 99);

}

BLOCK_TYPE TerrainGenerator::GetBlockTypeAtPos(vec3 pos)
{

    auto treeIter = treeBlocks.find(pos);
    if(treeIter != treeBlocks.end()){
        return treeIter->second;
    }
    
    int height = GetBlockHeightForPos(pos.x, pos.z) + 100;
    // std::cout << height << std::endl;
    BIOME biome = GetBiomeForPos(pos.x, pos.z);
    if(pos.y == height + 1 && biome == GRASSLAND  && rand() % 100 > 98){
        int treeHeight = rand() % 10 + 10; 
        for(int i = 0; i<treeHeight; i++){
            treeBlocks.insert(std::pair<vec3,BLOCK_TYPE> (vec3(pos.x, pos.y+i, pos.z), WOOD));


            // generate leaves if far enough up frum trunk
            if(i > (5 + rand() % 3)){
                for(int xFromTrunk = -5; xFromTrunk < 5; xFromTrunk++){
                    for(int zFromTrunk = -5; zFromTrunk < 5; zFromTrunk++){
                        if(xFromTrunk == 0 && zFromTrunk == 0){ // dont replace trunk with leaf
                            continue;
                        }
                        treeBlocks.insert(std::pair<vec3,BLOCK_TYPE> (vec3(pos.x+xFromTrunk, pos.y+i, pos.z+zFromTrunk), LEAVES));
                    }
                }
            }

            
        }
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