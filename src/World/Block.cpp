#include <Block.h>

NCraft::Block::Block(glm::vec3 pos, BLOCK_TYPE type)
{
    position = pos;
    this->type = type;
}
