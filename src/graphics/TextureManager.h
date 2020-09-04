#include "../world/Block.h"
#include <glm/glm.hpp>
#include <vector>
#include <map>
class TextureManager
{
public:
    static std::vector<glm::vec2> GetTextureForBlockFace(BLOCK_TYPE type, BLOCK_FACE face);
    static const int atlasSize = 4000;
    static const int pixelsPerSideOfFace = 32;
    static const std::map<BLOCK_TYPE, std::map<BLOCK_FACE, int>> numberOfFacesPerBlockType;
};