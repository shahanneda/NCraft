
#include <glm/glm.hpp>
#include "../Buffer.h"
#include "../Texture.h"
#include "../Shader.h"
#include "../../world/Block.h"

using glm::vec2;
using glm::vec3;
using std::vector;
class UIRenderer
{
public:
    UIRenderer();
    void Render();
    BLOCK_TYPE currentlySelectedBlockType = STONE;
    vector<BLOCK_TYPE> items = {GRASS, STONE, SAND, DIRT};

private:

    void RenderItemsOnHotbar();
    void RenderHotbar();
    void RenderCrosshair();
    Shader uiShader;
    UIBuffer uiBuffer;
    Texture crosshair;
    Texture hotbar;
    Texture atlas;
};
const vector<vec3> verts = {
    vec3(0, 1, 0), // top left
    vec3(1, 1, 0), // top right
    vec3(1, 0, 0), // bottom right
    vec3(0, 0, 0), // bottom left
};


const vector<int> indices = {0, 3, 2, 2, 1, 0};
const vector<vec2> textures = {
    vec2(0, 1),// top left
    vec2(1, 1), // top right
    vec2(1, 0),// bottom rigth
    vec2(0, 0) // bottom left
    };