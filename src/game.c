#include "player.h"
#include "camera.h"


void game(void)
{
    playerGetButtons();
    playerJump();
    playerMove();
    playerAttack();
    updateCamera();
    playerDraw();
}