
#include <glm/glm.hpp>
#include "../Buffer.h"
#include "../Texture.h"
#include "../Shader.h"

using glm::vec2;
using glm::vec3;
using std::vector;
class UIRenderer
{
public:
    UIRenderer();
    void Render();

private:
    Shader uiShader;
    UIBuffer uiBuffer;
    Texture crosshair;
    Texture hotbar;
    Texture atlas;
};
const vector<vec3> verts = {
    vec3(0,0,0),
    vec3(1,0,0),
    vec3(1,1,0),
    vec3(0,1,0),
};
const vector<int> indices = {0,3,2,2,1,0};
const vector<vec2> textures ={vec2(0, 0), vec2(1, 0), vec2(1, 1), vec2(0,1)};