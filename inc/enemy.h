#ifndef ENEMY_H
#define ENEMY_H

#include "goblin.h"



typedef struct _enemy_list
{
    GoblinsList_Typedef *goblinsList;

}EnemyList_Typedef, *EnemyCurrentList_Typedef;

typedef void (*EnemyInitHandler)    (EnemyList_Typedef*);
typedef void (*EnemyDrawHandler)    (EnemyList_Typedef*);
typedef void (*EnemyThinkHandler)   (EnemyList_Typedef*);

void enemyInit  (EnemyList_Typedef *enemyList);
void enemyDraw  (EnemyList_Typedef *enemyList);
void enemyThink (EnemyList_Typedef *enemyList);



typedef struct _enemy
{
    EnemyInitHandler    init;    
    EnemyDrawHandler    draw;  
    EnemyThinkHandler   think;  

}Enemy_Typedef;

extern Enemy_Typedef enemy;

#endif
