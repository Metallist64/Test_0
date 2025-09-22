#include "player.h"

void game(void)
{
    uint16_t input = JOY_readJoypad(0);
    //collisionResult = getCollision(level_0.collisions, COLLISION_VECTOR_DOWN);
    if((input & BUTTON_A) == BUTTON_A)
    {

        player.jumpPressed = true;           

    }
    else
    {

        player.jumpPressed = false;

    }

    playerJump();
    playerMove();

}