#include <genesis.h>
#include <kdebug.h>
#include "camera.h"
#include "game.h"
#include "player.h"
#include "level_0.h"

Game_Typedef game =
{
    .pCurrentLevel   = &level_0,
    .run             = gameProcessing,
    .lives           = 3,   
};

void gameProcessing(void)
{
    playerGetButtons();
    playerJump();
    playerMove();
    playerAttack();
    updateCamera();
    playerDraw();
}