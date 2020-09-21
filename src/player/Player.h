#ifndef PLAYER
#define PLAYER

#include "../world/Block.h"
#include "../graphics/Camera.h"
#include <glm/glm.hpp>
#include <vector>

using std::vector;
class Player{
    public:
        Player();
        void SwitchToItemNumber(int num);
        Camera camera;
        BLOCK_TYPE currentBlockTypeSelected = SAND;
        vector<BLOCK_TYPE> items = {GRASS, STONE, SAND, DIRT, WOOD};
};

#endif