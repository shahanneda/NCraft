
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Chunk.h"

using glm::vec2;
using glm::vec3;
Chunk::Chunk(vec3 pos) : blocks(), meshData(this), pos(pos)
{
    FillChunk();
    std::cout << "filled blocks for chunk at pos " << glm::to_string(pos) << std::endl;
}

void Chunk::FillChunk()
{
    BLOCK_TYPE type = pos.y > 0 ? AIR : GRASS;
    blocks.reserve(CHUNCK_SIZE * CHUNCK_SIZE * CHUNCK_SIZE);
    for (int x = 0; x < Chunk::CHUNCK_SIZE; x++)
    {
        for (int y = 0; y < Chunk::CHUNCK_SIZE; y++)
        {
            for (int z = 0; z < Chunk::CHUNCK_SIZE; z++)
            {
                SetBlock(Block(vec3(x, y, z), type));
            }
        }
    }
}

void Chunk::SetBlock(vec3 pos, Block b)
{
    blocks[pos.x + pos.y * CHUNCK_SIZE + pos.z * CHUNCK_SIZE * CHUNCK_SIZE] = b;
}
void Chunk::SetBlock(Block b)
{
    SetBlock(b.position, b);
}
Block *Chunk::GetBlockAt(glm::vec3 pos)
{
    return &blocks[pos.x + pos.y * CHUNCK_SIZE + pos.z * CHUNCK_SIZE * CHUNCK_SIZE];
}

bool Chunk::hasAllNeighbers()
{
    return positiveXNeighber && negativeXNeighber && positiveYNeighber && negativeYNeighber && positiveZNeighber && negativeZNeighber;
}

ChunkMeshData::ChunkMeshData(Chunk *chunk)
{
    this->chunk = chunk;
}

void ChunkMeshData::AddFace(BLOCK_FACE face, vector<vec3> *blockV, vector<int> *blockI, vector<vec2> *blockT)
{
    std::vector<int> faceIndices(faceIndicesOriginal);

    int numberOfFaceAlready = std::floorf(blockV->size() / 4); // check how many faces we already have
    for (int i = 0; i < faceIndices.size(); i++)
    {
        faceIndices[i] += numberOfFaceAlready * cubeVertFront.size(); // shift the indices, by faces*4 , since thats how much each face stores
    }

    switch (face)
    {
    case BLOCK_FACE::POS_X:
        blockV->insert(blockV->end(), cubeVertRight.begin(), cubeVertRight.end());
        break;

    case BLOCK_FACE::NEG_X:
        blockV->insert(blockV->end(), cubeVertLeft.begin(), cubeVertLeft.end());
        break;

    case BLOCK_FACE::POS_Y:
        blockV->insert(blockV->end(), cubeVertTop.begin(), cubeVertTop.end());
        break;

    case BLOCK_FACE::NEG_Y:
        blockV->insert(blockV->end(), cubeVertBottom.begin(), cubeVertBottom.end());
        break;

    case BLOCK_FACE::POS_Z:
        blockV->insert(blockV->end(), cubeVertBack.begin(), cubeVertBack.end());
        break;

    case BLOCK_FACE::NEG_Z:
        blockV->insert(blockV->end(), cubeVertFront.begin(), cubeVertFront.end());
        break;

    default:
        break;
    }

    blockI->insert(blockI->end(), faceIndices.begin(), faceIndices.end());
    blockT->insert(blockT->end(), faceTextureCoords.begin(), faceTextureCoords.end());
}

/// Checks and adds faces depending on whether the face has a transparent block beside it or not
void ChunkMeshData::AddAllNeededFaces(int x, int y, int z, vector<vec3> *blockV, vector<int> *blockI, vector<vec2> *blockT)
{
    // X
    if (x < Chunk::CHUNCK_SIZE - 1)
    { // -1 would be last block -2 is second last, bascially we dont want last
        if (chunk->GetBlockAt(vec3(x + 1, y, z))->isTransparent)
        {
            AddFace(BLOCK_FACE::POS_X, blockV, blockI, blockT);
        }
    }
    else if (chunk->positiveXNeighber->GetBlockAt(vec3(0, y, z))->isTransparent)
    { // chunk border
        AddFace(BLOCK_FACE::POS_X, blockV, blockI, blockT);
    }
    if (x > 0) // not first, since we are checking left
    {
        if (chunk->GetBlockAt(vec3(x - 1, y, z))->isTransparent)
        {
            AddFace(BLOCK_FACE::NEG_X, blockV, blockI, blockT);
        }
    }
    else if (chunk->negativeXNeighber->GetBlockAt(vec3(Chunk::CHUNCK_SIZE - 1, y, z))->isTransparent)
    { // chunk border
        AddFace(BLOCK_FACE::NEG_X, blockV, blockI, blockT);
    }

    // Y
    if (y < Chunk::CHUNCK_SIZE - 1)
    { // -1 would be last block -2 is second last, bascially we dont want last
        if (chunk->GetBlockAt(vec3(x, y + 1, z))->isTransparent)
        {
            AddFace(BLOCK_FACE::POS_Y, blockV, blockI, blockT);
        }
    }
    else if (chunk->positiveYNeighber->GetBlockAt(vec3(x, 0, z))->isTransparent)
    { // chunk border
        AddFace(BLOCK_FACE::POS_Y, blockV, blockI, blockT);
    }
    if (y > 0) // not first, since we are checking left
    {
        if (chunk->GetBlockAt(vec3(x, y - 1, z))->isTransparent)
        {
            AddFace(BLOCK_FACE::NEG_Y, blockV, blockI, blockT);
        }
    }
    else if (chunk->negativeYNeighber->GetBlockAt(vec3(x, Chunk::CHUNCK_SIZE - 1, z))->isTransparent)
    { // chunk border
        AddFace(BLOCK_FACE::NEG_Y, blockV, blockI, blockT);
    }

    // Z
    if (z < Chunk::CHUNCK_SIZE - 1)
    { // -1 would be last block -2 is second last, bascially we dont want last
        if (chunk->GetBlockAt(vec3(x, y, z + 1))->isTransparent)
        {
            AddFace(BLOCK_FACE::POS_Z, blockV, blockI, blockT);
        }
    }
    else if (chunk->negativeYNeighber->GetBlockAt(vec3(x, y, 0))->isTransparent)
    { // chunk border
        AddFace(BLOCK_FACE::POS_Z, blockV, blockI, blockT);
    }

    if (z > 0) // not first, since we are checking left
    {
        if (chunk->GetBlockAt(vec3(x, y, z - 1))->isTransparent)
        {
            AddFace(BLOCK_FACE::NEG_Z, blockV, blockI, blockT);
        }
    }
    else if (chunk->negativeYNeighber->GetBlockAt(vec3(x, y, Chunk::CHUNCK_SIZE - 1))->isTransparent)
    { // chunk border
        AddFace(BLOCK_FACE::NEG_Z, blockV, blockI, blockT);
    }

    // AddFace(BLOCK_FACE::POS_Z, blockV, blockI, blockT);
    // AddFace(BLOCK_FACE::NEG_Z, blockV, blockI, blockT);
}
void ChunkMeshData::GenerateData()
{
    generated = true;
    for (int x = 0; x < Chunk::CHUNCK_SIZE; x++)
    {
        for (int y = 0; y < Chunk::CHUNCK_SIZE; y++)
        {
            for (int z = 0; z < Chunk::CHUNCK_SIZE; z++)
            {
                Block *b = chunk->GetBlockAt(vec3(x, y, z));
                if (b->type == BLOCK_TYPE::AIR)
                {
                    continue;
                }

                // std::cout << glm::to_string(b->position) << std::endl;
                vector<vec3> blockV(0);
                vector<int> blockI(0);
                vector<vec2> blockT(0);

                // check and only draw faces where the blocks are air
                AddAllNeededFaces(x, y, z, &blockV, &blockI, &blockT);

                for (int i = 0; i < blockV.size(); i++)
                {
                    blockV[i] = blockV[i] + b->position; // move verts of block to the block pos
                }

                int addToIndices = verts.size(); // we need to shift the indices, according to how many vertices are already in the array; iteration is number of blocks, and we times it by size since each block has that many vertcis

                for (int i = 0; i < blockI.size(); i++)
                {
                    blockI[i] = blockI[i] + addToIndices;
                }
                verts.insert(verts.end(), blockV.begin(), blockV.end());
                indices.insert(indices.end(), blockI.begin(), blockI.end());
                textureCoords.insert(textureCoords.end(), blockT.begin(), blockT.end());
            }
        }
    }
}
