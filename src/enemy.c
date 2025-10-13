#include <genesis.h>
#include <kdebug.h>

#include "camera.h"
#include "enemy.h"
#include "game.h"
#include "goblin.h"

Enemy_Typedef enemy = 
{
    .init   = enemyInit,
    .draw   = enemyDraw,
    .AI     = enemyAI,
};

void enemyInit(EnemyList_Typedef *enemyList)
{
    goblinsInit(enemyList->goblinsList);    
    
}

void enemyDraw(EnemyList_Typedef *enemyList)
{
    goblinsDraw(enemyList->goblinsList);

}

void enemyAI(EnemyList_Typedef *enemyList)
{
    goblinsAI(enemyList->goblinsList);
}




