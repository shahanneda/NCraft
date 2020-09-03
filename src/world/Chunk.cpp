
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Chunk.h"

using glm::vec2;
using glm::vec3;
Chunk::Chunk() : blocks(), meshData(this)
{
    FillChunk();
    meshData.GenerateData();
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
            x = 0;
            y = 0;
            z++;
        }
    }
}

Block *Chunk::GetBlockAt(glm::vec3 pos)
{
    return &blocks[pos.x + pos.y * CHUNCK_SIZE + pos.z * CHUNCK_SIZE * CHUNCK_SIZE];
}

ChunkMeshData::ChunkMeshData(Chunk *chunk)
{
    this->chunk = chunk;
}

void ChunkMeshData::GenerateData()
{
    for (int x = 0; x < Chunk::CHUNCK_SIZE; x++)
    {
        for (int y = 0; y < Chunk::CHUNCK_SIZE; y++)
        {
            for (int z = 0; z < Chunk::CHUNCK_SIZE; z++)
            {
                Block *b = chunk->GetBlockAt(vec3(x, y, z));
                std::cout << glm::to_string(b->position) << std::endl;
                vector<vec3> blockV(cubeVerts);
                vector<int> blockI(cubeIndices);

                for (int i = 0; i < blockV.size(); i++)
                {
                    blockV[i] = blockV[i] + b->position;
                }
                int iteration = z + y * Chunk::CHUNCK_SIZE + x * Chunk::CHUNCK_SIZE * Chunk::CHUNCK_SIZE;
                int addToIndices = iteration * blockV.size(); // we need to shift the indices, according to how many vertices are already in the array; iteration is number of blocks, and we times it by size since each block has that many vertcis

                for (int i = 0; i < blockI.size(); i++)
                {
                    blockI[i] = blockI[i] + addToIndices;
                }
                verts.insert(verts.end(), blockV.begin(), blockV.end());
                indices.insert(indices.end(), blockI.begin(), blockI.end());
                textureCoords.insert(textureCoords.end(), cubeTexCoords.begin(), cubeTexCoords.end());
            }
        }
    }
}
