#include <genesis.h>
#include <kdebug.h>
#include "enemy.h"
#include "game.h"
#include "goblin.h"
#include "camera.h"


void enemyInit(void)
{
    for(uint16_t goblinsIdx = 0; goblinsIdx <  game.currentLevel->enemyList->goblinsCnt; goblinsIdx++)
    {
        game.currentLevel->enemyList->listGoblins[goblinsIdx].sprite = SPR_addSprite(game.currentLevel->enemyList->listGoblins[goblinsIdx].spriteDef, 0, 0, TILE_ATTR(PAL3, TRUE, FALSE, TRUE));
        SPR_setVisibility(game.currentLevel->enemyList->listGoblins[goblinsIdx].sprite, HIDDEN);
        SPR_setPosition(    game.currentLevel->enemyList->listGoblins[goblinsIdx].sprite, 
                            game.currentLevel->enemyList->listGoblins[goblinsIdx].globalPosition.x, 
                            game.currentLevel->enemyList->listGoblins[goblinsIdx].globalPosition.y);
    
    KDebug_AlertNumber(goblinsIdx);
    KDebug_AlertNumber(game.currentLevel->enemyList->listGoblins[goblinsIdx].globalPosition.x);
    KDebug_AlertNumber(game.currentLevel->enemyList->listGoblins[goblinsIdx].globalPosition.y);

    }
    
}

void enemyDraw(void)
{

    for(uint16_t goblinsIdx = 0; goblinsIdx <  game.currentLevel->enemyList->goblinsCnt; goblinsIdx++)
    {
        enemyDrawLocal(&game.currentLevel->enemyList->listGoblins[goblinsIdx]);
    }
}

void enemyDrawLocal(Goblin_Typedef *goblin)
{
    int16_t localPositionX = goblin->globalPosition.x - playerCamera.viewZone.left;
    int16_t localPositionY = goblin->globalPosition.y - playerCamera.viewZone.top;

    if((localPositionX > 320)|| (localPositionX < -32)||(localPositionY > 240)|| (localPositionY < 0))
    {
        SPR_setVisibility(goblin->sprite, HIDDEN);
    }
    else
    {   
        SPR_setPosition(goblin->sprite, localPositionX, localPositionY);
        SPR_setVisibility(goblin->sprite, VISIBLE);
    }

}