#include "Block.h"
#include <iostream>

#include <glm/gtx/string_cast.hpp>
#include "Chunk.h"
NCraft::Block::Block(glm::vec3 pos, BLOCK_TYPE type, Chunk *chunk)
{
    this->position = pos;
    this->type = type;
    this->chunk = chunk;
    if (type == BLOCK_TYPE::AIR)
    {
        isTransparent = true;
    }
    else
    {
        isTransparent = false;
    }
}
glm::vec3 NCraft::Block::GetWorldPos()
{
    vec3 chunkPos = chunk->GetWorldPos();
    return vec3(chunkPos.x + position.x, chunkPos.y + position.y, chunkPos.z + position.z);
}
