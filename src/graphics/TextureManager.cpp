
#include "TextureManager.h"
#include <iostream>

using glm::vec2;
using std::vector;

const std::map<BLOCK_TYPE, std::map<BLOCK_FACE, int>> TextureManager::numberOfFacesPerBlockType = {
    // this stores what faces each blocks use
    {
        GRASS,
        {{POS_X, 0},
         {NEG_X, 0},
         {POS_Z, 0},
         {NEG_Z, 0},
         {POS_Y, 1},
         {NEG_Y, 0}}},
};
std::vector<glm::vec2> TextureManager::GetTextureForBlockFace(BLOCK_TYPE type, BLOCK_FACE face)
{
    int faceIndex = numberOfFacesPerBlockType.find(type)->second.find(face)->second;
    auto faceIndexWithPixels = faceIndex * pixelsPerSideOfFace;

    float leftX = (float)faceIndexWithPixels / (float)atlasSize;
    float rightX = ((float)faceIndexWithPixels + pixelsPerSideOfFace) / (float)atlasSize; // same as 1
    float topY = 0;
    float bottomY = (float)32 / (float)atlasSize;
    ;

    // float rightSide = ((float)faceIndexWithPixels + pixelsPerSideOfFace) / (float)atlasSize; // same as 1
    // float leftSide = (float)faceIndexWithPixels / (float)atlasSize;                          // same as 0
    // float rightSide = ((float)faceIndexWithPixels + pixelsPerSideOfFace) / (float)atlasSize; // same as 1
    std::cout << faceIndex << leftX << " " << rightX << " " << bottomY << " " << std::endl;

    std::vector<vec2> coords = {
        vec2(leftX, bottomY),   // bottom left
        vec2(leftX, topY),      // top  left
        vec2(rightX, topY),     // top rigth
        vec2(rightX, bottomY)}; // bottom right
    return coords;
}