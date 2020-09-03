
#include <iostream>
#include <glm/glm.hpp>
#include "Chunk.h"

Chunk::Chunk() : blocks()
{
    FillChunk();
}

void Chunk::FillChunk()
{
    int x = 0;
    int y = 0;
    int z = 0;
    for (int i = 0; i < CHUNCK_SIZE * CHUNCK_SIZE * CHUNCK_SIZE; i++)
    {
        blocks.push_back(Block(glm::vec3(x, y, z), BLOCK_TYPE::GRASS));
        x++;
        if (x == CHUNCK_SIZE)
        {
            x = 0;
            y++;
        }
        if (y == CHUNCK_SIZE)
        {
            y = 0;
            z++;
        }
    }
}

Block *Chunk::GetBlockAt(glm::vec3 pos)
{
    return &blocks[pos.x + pos.y * CHUNCK_SIZE + pos.z * CHUNCK_SIZE];
}