#ifndef NCRAFT_BLOCK
#define NCRAFT_BLOCK
#include <glm/glm.hpp>

enum BLOCK_TYPE
{
    GRASS,
    STONE,
};
namespace NCraft
{
    class Block
    {
    public:
        Block(glm::vec3 pos, BLOCK_TYPE type);
        glm::vec3 position;
        BLOCK_TYPE type;
    };
} // namespace NCraft
#endif