#include <genesis.h>
#include <kdebug.h>
#include "camera.h"
#include "enemy.h"
#include "game.h"
#include "player.h"
#include "level_0.h"

Game_Typedef game =
{
    .currentLevel   = &level_0,
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
    enemy.AI    (&enemyListLevel_0);
    enemy.draw  (&enemyListLevel_0);

}