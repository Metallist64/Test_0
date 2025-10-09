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

void goblinsThink (GoblinsList_Typedef *goblinsList)
{
    for (uint16_t goblinsIdx = 0; goblinsIdx < goblinsList->cnt; goblinsIdx++)
    {
        goblinThink(goblinsList->list + goblinsIdx);
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

void goblinThink(Goblin_Typedef *goblin)
{
    int16_t distanceX = player.globalPosition.x - goblin->globalPosition.x;
    uint16_t absDistanceX = abs(distanceX);

    switch (goblin->state)
    {
        case GOBLIN_THINK:

            if( (distanceX > 50) && (distanceX < 150) )
            {
                goblin->state = GOBLIN_ATTACK;
            }
            else
            {
                goblin->state = GOBLIN_WALK;       
            }
            //KDebug_Alert("GOBLIN THINK");

        break;

        case GOBLIN_WALK:

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

        break;
        
        case GOBLIN_ATTACK:

            goblin->animState = GOBLIN_ANIM_ATTACK;
            goblin->state = GOBLIN_TICKS;
            //KDebug_Alert("GOBLIN ATTACK");

        break;


        case GOBLIN_STAY:
            
            //KDebug_Alert("GOBLIN STAY");
            //goblin->state = 

        break;
    
        case GOBLIN_DIE:

            //KDebug_Alert("GOBLIN DIE");

        break;        

        case GOBLIN_TICKS:
        
            goblin->thinkTicksCnt--;
            if(goblin->thinkTicksCnt == 0) 
            {
                goblin->thinkTicksCnt = goblin->thinkTicks;
                goblin->state = GOBLIN_THINK;
            }
           // KDebug_Alert("GOBLIN TICKS");
            //KDebug_AlertNumber();

        break;         



        case GOBLIN_IDLE:


        break;


        default:

        break;
    }    


}
