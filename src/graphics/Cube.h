#include <vector>
#include <glm/glm.hpp>
using glm::vec2;
using glm::vec3;
struct Cube
{

    std::vector<int> indices = {
        0, 1, 2, //  front face
        2, 3, 0, //

        4, 5, 6, // right
        6, 7, 4, //

        8, 9, 10,  // back
        10, 11, 8, //

        12, 13, 14, // left
        14, 15, 12, //

        16, 17, 18, // top
        18, 19, 16, //

        20, 21, 22, // bottom
        22, 23, 20  //

    };
    std::vector<vec3> vertices = {
        //front face
        vec3(0, 0, 0), // 0 bottom left
        vec3(0, 1, 0), // 1 top left
        vec3(1, 1, 0), // 2 top right
        vec3(1, 0, 0), // 3 bottom right

        //right face
        vec3(1, 0, 0), // bottom left
        vec3(1, 0, 1), // bottom right
        vec3(1, 1, 1), // top right
        vec3(1, 1, 0), // top left

        // back face
        vec3(1, 0, 1), // 7 bottom left
        vec3(0, 0, 1), // 8 bottom right
        vec3(0, 1, 1), // 9 top right
        vec3(1, 1, 1), // 10 top left

        // left face
        vec3(0, 0, 1), // bottom left
        vec3(0, 0, 0), // bottom right
        vec3(0, 1, 0), // top right
        vec3(0, 1, 1), // top left

        // top face
        vec3(0, 1, 0), // bottom left
        vec3(1, 1, 0), // bottom right
        vec3(1, 1, 1), // top right
        vec3(0, 1, 1), // top left

        // bottom face
        vec3(0, 0, 0), // bottom left
        vec3(1, 0, 0), // bottom right
        vec3(1, 0, 1), // top right
        vec3(0, 0, 1)  // top left
    };
    std::vector<vec2>
        texCoords = {vec2(0, 0), vec2(0, 1), vec2(1, 1), vec2(1, 0),

                     vec2(0, 0), vec2(0, 1), vec2(1, 1), vec2(1, 0),

                     vec2(0, 0), vec2(0, 1), vec2(1, 1), vec2(1, 0),

                     vec2(0, 0), vec2(0, 1), vec2(1, 1), vec2(1, 0),

                     vec2(0, 0), vec2(0, 1), vec2(1, 1), vec2(1, 0),

                     vec2(0, 0), vec2(0, 1), vec2(1, 1), vec2(1, 0)};
};