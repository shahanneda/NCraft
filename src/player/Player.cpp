#include "Player.h"

Player::Player() : camera(glm::vec3(0,100,3)){


}

void Player::SwitchToItemNumber(int num){
    // TODO: do bounds checking here
    currentBlockTypeSelected = items[num];
}



