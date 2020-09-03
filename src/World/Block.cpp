#include "Block.h"
#include <iostream>

#include <glm/gtx/string_cast.hpp>
NCraft::Block::Block(glm::vec3 pos, BLOCK_TYPE type)
{
    this->position = pos;
    this->type = type;
}
