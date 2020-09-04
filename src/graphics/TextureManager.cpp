
#include "TextureManager.h"
#include <iostream>

using glm::vec2;
using std::vector;

const std::map<BLOCK_TYPE, std::map<BLOCK_FACE, int>> TextureManager::numberOfFacesPerBlockType = {
    // this stores what faces each blocks use
    {
        {GRASS,
         {{POS_X, 0},
          {NEG_X, 0},
          {POS_Z, 0},
          {NEG_Z, 0},
          {POS_Y, 1},
          {NEG_Y, 2}}},
        {DIRT,
         {{POS_X, 2},
          {NEG_X, 2},
          {POS_Z, 2},
          {NEG_Z, 2},
          {POS_Y, 2},
          {NEG_Y, 2}}}

    },
};
std::vector<glm::vec2> TextureManager::GetTextureForBlockFace(BLOCK_TYPE type, BLOCK_FACE face)
{
    int faceIndex = numberOfFacesPerBlockType.find(type)->second.find(face)->second;
    auto faceIndexWithPixels = faceIndex * pixelsPerSideOfFace;

    float adjustmentFactor = (1.0f / (float)atlasSize) * 1 / 2.0f;

    float leftX = ((float)faceIndexWithPixels / (float)atlasSize) + adjustmentFactor;
    float rightX = (((float)faceIndexWithPixels + pixelsPerSideOfFace) / (float)atlasSize) - adjustmentFactor; //
    float topY = 0 + adjustmentFactor;
    float bottomY = ((float)32 / (float)atlasSize) - adjustmentFactor;
    ;

    // float rightSide = ((float)faceIndexWithPixels + pixelsPerSideOfFace) / (float)atlasSize; // same as 1
    // float leftSide = (float)faceIndexWithPixels / (float)atlasSize;                          // same as 0
    // float rightSide = ((float)faceIndexWithPixels + pixelsPerSideOfFace) / (float)atlasSize; // same as 1

    std::vector<vec2> coords = {
        vec2(leftX, bottomY),  // bottom left
        vec2(rightX, bottomY), // bottom right
        vec2(rightX, topY),    // top  rigth
        vec2(leftX, topY),     // top left
    };
    return coords;
}