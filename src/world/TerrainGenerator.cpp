#include "TerrainGenerator.h"

using glm::vec3;
TerrainGenerator::TerrainGenerator() : noise()
{
}

BLOCK_TYPE TerrainGenerator::GetBlockTypeAtPos(vec3 pos)
{

    if (pos.y == 15)
    {
        return GRASS;
    }

    if (pos.y < 16)
    {
        return DIRT;
    }

    return AIR;
}
