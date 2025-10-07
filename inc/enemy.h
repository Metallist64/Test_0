#ifndef ENEMY_H
#define ENEMY_H

#include "goblin.h"


void enemyDraw(void);
void enemyInit(void);
void enemyDrawLocal(Goblin_Typedef *goblin);

typedef struct _monsters
{
    Goblin_Typedef *listGoblins;
    uint16_t        goblinsCnt;

}Monsters_Typedef;

#endif