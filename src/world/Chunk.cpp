
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Chunk.h"
#include "../graphics/TextureManager.h"
#include <FastNoise/FastNoise.h>
#include <thread>

using glm::vec2;
using glm::vec3;
Chunk::Chunk(vec3 pos, TerrainGenerator *terrainGen) : meshData(this), pos(pos)
{
    this->terrainGen = terrainGen;
    FillChunk();

    meshData.verts.push_back(vec3(0,0,0));
    meshData.normals.push_back(vec3(0,0,0));
    meshData.textureCoords.push_back(vec2(0,0));
    meshData.indices.push_back(0);
    // std::thread t1(&Chunk::FillChunk, this);
    // t1.detach();
}

vec3 Chunk::GetWorldPos()
{
    return vec3(pos.x * CHUNCK_SIZE, pos.y * CHUNCK_SIZE, pos.z * CHUNCK_SIZE);
}
void Chunk::FillChunk()
{

    BLOCK_TYPE type = pos.y > 0 ? AIR : GRASS;
    blocks.reserve(CHUNCK_SIZE * CHUNCK_SIZE * CHUNCK_SIZE);
    for (int z = 0; z < Chunk::CHUNCK_SIZE; z++)
    {
        for (int y = 0; y < Chunk::CHUNCK_SIZE; y++)
        {
            for (int x = 0; x < Chunk::CHUNCK_SIZE; x++)
            {
                vec3 worldPos = vec3(x + pos.x * CHUNCK_SIZE, y + pos.y * CHUNCK_SIZE, z + pos.z * CHUNCK_SIZE);
                blocks.push_back(Block(vec3(x, y, z), terrainGen->GetBlockTypeAtPos(worldPos), this));
            }
        }
    }

    terrainGen->blockHeights.clear(); // reset the hash map used for memonization
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

ChunkMeshData::ChunkMeshData(Chunk *chunk) : verts(), indices(), textureCoords(), normals()
{
    this->chunk = chunk;
    indices.push_back(0);
    // indices.erase(indices.begin());
}

void ChunkMeshData::AddFace(BLOCK_TYPE type, BLOCK_FACE face, vector<vec3> *blockV, vector<int> *blockI, vector<vec2> *blockT, vector<vec3> *blockN)
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
        blockN->insert(blockN->end(), cubeNormRight.begin(), cubeNormRight.end());
        break;

    case BLOCK_FACE::NEG_X:
        blockV->insert(blockV->end(), cubeVertLeft.begin(), cubeVertLeft.end());
        blockN->insert(blockN->end(), cubeNormLeft.begin(), cubeNormLeft.end());
        break;

    case BLOCK_FACE::POS_Y:
        blockV->insert(blockV->end(), cubeVertTop.begin(), cubeVertTop.end());
        blockN->insert(blockN->end(), cubeNormTop.begin(), cubeNormTop.end());
        break;

    case BLOCK_FACE::NEG_Y:
        blockV->insert(blockV->end(), cubeVertBottom.begin(), cubeVertBottom.end());
        blockN->insert(blockN->end(), cubeNormBottom.begin(), cubeNormBottom.end());
        break;

    case BLOCK_FACE::POS_Z:
        blockV->insert(blockV->end(), cubeVertBack.begin(), cubeVertBack.end());
        blockN->insert(blockN->end(), cubeNormBack.begin(), cubeNormBack.end());
        break;

    case BLOCK_FACE::NEG_Z:
        blockV->insert(blockV->end(), cubeVertFront.begin(), cubeVertFront.end());
        blockN->insert(blockN->end(), cubeNormFront.begin(), cubeNormFront.end());
        break;

    default:
        break;
    }
    auto texCoords = TextureManager::GetTextureForBlockFace(type, face);
    blockI->insert(blockI->end(), faceIndices.begin(), faceIndices.end());
    blockT->insert(blockT->end(), texCoords.begin(), texCoords.end()); // texture manager get texture coords for blocktpye
}

/// Checks and adds faces depending on whether the face has a transparent block beside it or not
void ChunkMeshData::AddAllNeededFaces(int x, int y, int z, BLOCK_TYPE type, vector<vec3> *blockV, vector<int> *blockI, vector<vec2> *blockT, vector<vec3> *blockN)
{
    // X
    if (x < Chunk::CHUNCK_SIZE - 1)
    { // -1 would be last block -2 is second last, bascially we dont want last
        if (chunk->GetBlockAt(vec3(x + 1, y, z))->isTransparent)
        {
            AddFace(type, BLOCK_FACE::POS_X, blockV, blockI, blockT, blockN);
        }
    }
    else if (chunk->positiveXNeighber->GetBlockAt(vec3(0, y, z))->isTransparent)
    { // chunk border
        AddFace(type, BLOCK_FACE::POS_X, blockV, blockI, blockT, blockN);
    }
    if (x > 0) // not first, since we are checking left
    {
        if (chunk->GetBlockAt(vec3(x - 1, y, z))->isTransparent)
        {
            AddFace(type, BLOCK_FACE::NEG_X, blockV, blockI, blockT, blockN);
        }
    }
    else if (chunk->negativeXNeighber->GetBlockAt(vec3(Chunk::CHUNCK_SIZE - 1, y, z))->isTransparent)
    { // chunk border
        AddFace(type, BLOCK_FACE::NEG_X, blockV, blockI, blockT, blockN);
    }

    // Y
    if (y < Chunk::CHUNCK_SIZE - 1)
    { // -1 would be last block -2 is second last, bascially we dont want last
        if (chunk->GetBlockAt(vec3(x, y + 1, z))->isTransparent)
        {
            AddFace(type, BLOCK_FACE::POS_Y, blockV, blockI, blockT, blockN);
        }
    }
    else if (chunk->positiveYNeighber->GetBlockAt(vec3(x, 0, z))->isTransparent)
    { // chunk border
        AddFace(type, BLOCK_FACE::POS_Y, blockV, blockI, blockT, blockN);
    }
    if (y > 0) // not first, since we are checking left
    {
        if (chunk->GetBlockAt(vec3(x, y - 1, z))->isTransparent)
        {
            AddFace(type, BLOCK_FACE::NEG_Y, blockV, blockI, blockT, blockN);
        }
    }
    else if (chunk->negativeYNeighber->GetBlockAt(vec3(x, Chunk::CHUNCK_SIZE - 1, z))->isTransparent)
    { // chunk border
        AddFace(type, BLOCK_FACE::NEG_Y, blockV, blockI, blockT, blockN);
    }

    // Z
    if (z < Chunk::CHUNCK_SIZE - 1)
    { // -1 would be last block -2 is second last, bascially we dont want last
        if (chunk->GetBlockAt(vec3(x, y, z + 1))->isTransparent)
        {
            AddFace(type, BLOCK_FACE::POS_Z, blockV, blockI, blockT, blockN);
        }
    }
    else if (chunk->positiveZNeighber->GetBlockAt(vec3(x, y, 0))->isTransparent)
    { // chunk border
        AddFace(type, BLOCK_FACE::POS_Z, blockV, blockI, blockT, blockN);
    }

    if (z > 0) // not first, since we are checking left
    {
        if (chunk->GetBlockAt(vec3(x, y, z - 1))->isTransparent)
        {
            AddFace(type, BLOCK_FACE::NEG_Z, blockV, blockI, blockT, blockN);
        }
    }
    else if (chunk->negativeZNeighber->GetBlockAt(vec3(x, y, Chunk::CHUNCK_SIZE - 1))->isTransparent)
    { // chunk border
        AddFace(type, BLOCK_FACE::NEG_Z, blockV, blockI, blockT, blockN);
    }

    // AddFace(BLOCK_FACE::POS_Z, blockV, blockI, blockT);
    // AddFace(BLOCK_FACE::NEG_Z, blockV, blockI, blockT);
}

void ChunkMeshData::GenerateDataThread()
{
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
                vector<vec3> blockN(0);

                // check and only draw faces where the blocks are air
                AddAllNeededFaces(x, y, z, b->type, &blockV, &blockI, &blockT, &blockN);

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
                normals.insert(normals.end(), blockN.begin(), blockN.end());
            }
        }
    }
}
void ChunkMeshData::GenerateData()
{
    generated = true;
    verts.clear();
    indices.clear();
    textureCoords.clear();
    normals.clear();
    this->GenerateDataThread();
    // std::thread t1(&ChunkMeshData::GenerateDataThread, this);
    // t1.detach();
}

Chunk::~Chunk()
{
}
ChunkMeshData::~ChunkMeshData()
{

    verts.push_back(vec3(0, 0, 0));
    textureCoords.push_back(vec2(0,0));
    normals.push_back(vec3(0,0,0));
    normals.push_back(vec3(0,0,0));
    indices.push_back(0);
    // this is just to avoid somesort of bug with the vector destructor
    // verts.clear();
    // indices.clear();
    // textureCoords.clear();
}