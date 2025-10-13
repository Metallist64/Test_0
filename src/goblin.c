#include <genesis.h>
#include <kdebug.h>
#include "camera.h"
#include "goblin.h"
#include "resources.h"
#include "player.h"



void goblinsInit(GoblinsList_Typedef *goblinsList)
{
    for(uint16_t goblinIdx = 0; goblinIdx < goblinsList->cnt; goblinIdx++)
    {
        goblinsList->list[goblinIdx].sprite = SPR_addSprite(goblinsList->list[goblinIdx].spriteDef, 0, 0, TILE_ATTR(PAL3, TRUE, FALSE, TRUE));
        SPR_setVisibility(goblinsList->list[goblinIdx].sprite, HIDDEN);
        SPR_setPosition(goblinsList->list[goblinIdx].sprite, goblinsList->list[goblinIdx].globalPosition.x, goblinsList->list[goblinIdx].globalPosition.y);
    }
}

void goblinsAI (GoblinsList_Typedef *goblinsList)
{
    for (uint16_t goblinsIdx = 0; goblinsIdx < goblinsList->cnt; goblinsIdx++)
    {
        goblinAI(goblinsList->list + goblinsIdx);
    }
}

void goblinsDraw(GoblinsList_Typedef *goblinsList)
{
    Goblin_Typedef *goblin          = NULL;
    int16_t         localPositionX  = 0,
                    localPositionY  = 0;
    
    for (uint16_t goblinsIdx = 0; goblinsIdx < goblinsList->cnt; goblinsIdx++)
    {
        goblin = &goblinsList->list[goblinsIdx];
        localPositionX = goblin->globalPosition.x - playerCamera.viewZone.left;
        localPositionY = goblin->globalPosition.y - playerCamera.viewZone.top;

        if((localPositionX > 320)|| (localPositionX < -32)||(localPositionY > 240)|| (localPositionY < 0))
        {
            SPR_setVisibility(goblin->sprite, HIDDEN);
        }
        else
        {  
            SPR_setHFlip(goblin->sprite, goblin->direction);             
            SPR_setPosition(goblin->sprite, localPositionX, localPositionY);
            SPR_setVisibility(goblin->sprite, VISIBLE);
            SPR_setAnim(goblin->sprite, goblin->animState);
        }
    }
}

void goblinAI(Goblin_Typedef *goblin)
{
    switch (goblin->state)
    {
        case GOBLIN_THINK:  goblinAI_Think(goblin);     break;
        case GOBLIN_WALK:   goblinAI_Walk(goblin);      break;
        case GOBLIN_ATTACK: goblinAI_Attack(goblin);    break;
        case GOBLIN_STAY:   goblinAI_Stay(goblin);      break;
        case GOBLIN_DIE:    goblinAI_Die(goblin);       break;
        case GOBLIN_TICKS:  goblinAI_Ticks(goblin);     break;
        case GOBLIN_IDLE:   goblinAI_Idle(goblin);      break;
    }    
}

void goblinAI_Think(Goblin_Typedef *goblin)
{

    int16_t distanceX = player.globalPosition.x - goblin->globalPosition.x;
    uint16_t absDistanceX = abs(distanceX);    

    if( (distanceX > 50) && (distanceX < 150) )
    {
        goblin->state = GOBLIN_ATTACK;
    }
    else
    {
        goblin->state = GOBLIN_WALK;       
    }
}

void goblinAI_Walk(Goblin_Typedef *goblin)
{

    int16_t distanceX = player.globalPosition.x - goblin->globalPosition.x;
    uint16_t absDistanceX = abs(distanceX);    

    if(distanceX > 0)
    {
        goblin->animState = GOBLIN_ANIM_WALK;
        goblin->direction = GOBLIN_DIR_FORWARD;
        goblin->globalPosition.x++;
    } 
    else
    {
        goblin->animState = GOBLIN_ANIM_WALK;
        goblin->direction = GOBLIN_DIR_BACKWARD;
        goblin->globalPosition.x--;
    }
    goblin->state = GOBLIN_TICKS;
    //KDebug_Alert("GOBLIN WALK");
}

void goblinAI_Attack(Goblin_Typedef *goblin)
{
    goblin->animState = GOBLIN_ANIM_ATTACK;
    goblin->state = GOBLIN_TICKS;
    //KDebug_Alert("GOBLIN ATTACK");
}

void goblinAI_Stay(Goblin_Typedef *goblin)
{


}

void goblinAI_Die(Goblin_Typedef *goblin)
{
    if(SPR_isAnimationDone(goblin->sprite))
    {
        SPR_setAnimationLoop(goblin->sprite, false);
        goblin->state       = GOBLIN_IDLE;
        //while(1)    ;
    }
}

void goblinAI_Ticks(Goblin_Typedef *goblin)
{
    goblin->thinkTicksCnt--;
    if(goblin->thinkTicksCnt == 0) 
    {
        goblin->thinkTicksCnt = goblin->thinkTicks;
        goblin->state = GOBLIN_THINK;
    }
}

void goblinAI_Idle(Goblin_Typedef *goblin)
{


}


