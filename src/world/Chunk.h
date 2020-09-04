#include "Block.h"
#include <vector>
#ifndef NCRAFT_CHUNK
#define NCRAFT_CHUNK

using namespace NCraft;
using glm::vec2;
using glm::vec3;
using std::vector;

class Chunk; // forward dec
class ChunkMeshData
{
public:
    vector<glm::vec3> verts;
    vector<int> indices;
    vector<glm::vec2> textureCoords;
    ChunkMeshData(Chunk *chunk);
    Chunk *chunk;
    bool generated = false;
    void GenerateData();
    void AddFace(BLOCK_TYPE type, BLOCK_FACE face, vector<vec3> *blockV, vector<int> *blockI, vector<vec2> *blockT);
    void AddAllNeededFaces(int x, int y, int z, BLOCK_TYPE type, vector<vec3> *blockV, vector<int> *blockI, vector<vec2> *blockT);

private:
    const std::vector<int> faceIndicesOriginal = {
        0, 1, 2, //  front face
        2, 3, 0, //
    };
};
const std::vector<vec3> cubeVertFront = {
    //front face
    vec3(0, 0, 0), // 0 bottom left
    vec3(0, 1, 0), // 1 top left
    vec3(1, 1, 0), // 2 top right
    vec3(1, 0, 0), // 3 bottom right
};

const std::vector<vec3> cubeVertRight = {
    //right face
    vec3(1, 0, 0), // bottom left
    vec3(1, 0, 1), // bottom right
    vec3(1, 1, 1), // top right
    vec3(1, 1, 0), // top left

};
const std::vector<vec3> cubeVertBack = {
    // back face
    vec3(1, 0, 1), // 7 bottom left
    vec3(0, 0, 1), // 8 bottom right
    vec3(0, 1, 1), // 9 top right
    vec3(1, 1, 1), // 10 top left
};

const std::vector<vec3> cubeVertLeft = {
    // left face
    vec3(0, 0, 1), // bottom left
    vec3(0, 0, 0), // bottom right
    vec3(0, 1, 0), // top right
    vec3(0, 1, 1), // top left
};

const std::vector<vec3> cubeVertTop = {
    // top face
    vec3(0, 1, 0), // bottom left
    vec3(1, 1, 0), // bottom right
    vec3(1, 1, 1), // top right
    vec3(0, 1, 1), // top left
};

const std::vector<vec3> cubeVertBottom = {
    // bottom face
    vec3(0, 0, 0), // bottom left
    vec3(1, 0, 0), // bottom right
    vec3(1, 0, 1), // top right
    vec3(0, 0, 1)  // top left
};

class Chunk
{
public:
    const static int CHUNCK_SIZE = 16;
    Chunk(vec3 pos);
    vector<Block> blocks;
    vec3 pos;
    ChunkMeshData meshData;
    void FillChunk();
    Block *GetBlockAt(glm::vec3 pos);
    void SetBlock(vec3 pos, Block b);
    void SetBlock(Block b);

    bool hasAllNeighbers();
    Chunk *positiveXNeighber = nullptr;
    Chunk *negativeXNeighber = nullptr;

    Chunk *positiveYNeighber = nullptr;
    Chunk *negativeYNeighber = nullptr;

    Chunk *positiveZNeighber = nullptr;
    Chunk *negativeZNeighber = nullptr;
};

#endif