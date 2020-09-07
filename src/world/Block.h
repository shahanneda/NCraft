#ifndef NCRAFT_BLOCK
#define NCRAFT_BLOCK
#include <glm/glm.hpp>

class Chunk;
enum BLOCK_TYPE
{
    GRASS,
    DIRT,
    STONE,
    AIR,
};

enum BLOCK_FACE
{
    POS_X,
    NEG_X,
    POS_Y,
    NEG_Y,
    POS_Z,
    NEG_Z
};
namespace NCraft
{
    class Block
    {
    public:
        Block(glm::vec3 pos, BLOCK_TYPE type, Chunk *chunk);
        glm::vec3 position;
        BLOCK_TYPE type;
        bool isTransparent;
        Chunk *chunk;
        glm::vec3 GetWorldPos();

    private:
        // Block(const Block& that);
        // Block &operator=(const Block &that);
    };
} // namespace NCraft
#endif