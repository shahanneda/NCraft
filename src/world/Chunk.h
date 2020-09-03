#include "Block.h"
#include <vector>
using namespace NCraft;
using std::vector;
class Chunk
{
public:
    const static int CHUNCK_SIZE = 16;
    Chunk();
    vector<Block> blocks;
    void FillChunk();
    Block GetBlockAt(glm::vec3 pos);
};