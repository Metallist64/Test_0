#include <genesis.h>
#include <kdebug.h>

#include "camera.h"
#include "goblin.h"
#include "memory.h"
#include "player.h"
#include "resources.h"

void goblinBlink(Goblin_Typedef *goblin)
{
    goblin->blink.periodCnt--; 
    goblin->blink.ticksCnt--;
    if (goblin->blink.periodCnt != 0 && goblin->health > 0)
    {
        if(goblin->blink.ticksCnt == 0)
        {
            goblin->blink.visibility    = !goblin->blink.visibility;
            goblin->blink.ticksCnt      = goblin->blink.ticks;
        }
    }
    else
    {
        goblin->blink.visibility = VISIBLE;
        goblin->blink.ticksCnt  =  goblin->blink.ticks;
        goblin->blink.periodCnt = goblin->blink.period;     
        goblin->blink.En   = false;
    }    
}

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
    
    for (uint16_t goblinsIdx = 0; goblinsIdx < goblinsList->cnt; goblinsIdx++)
    {
        goblin = &goblinsList->list[goblinsIdx];
        goblin->localPosition.x = goblin->globalPosition.x - playerCamera.viewZone.left;
        goblin->localPosition.y = goblin->globalPosition.y - playerCamera.viewZone.top; 

        if( player.globalPosition.x - goblin->globalPosition.x > 0)  goblin->flip = false;
        else                                                         goblin->flip = true;        

        if((goblin->localPosition.x > 320)|| (goblin->localPosition.x < -32)||(goblin->localPosition.y > 240)|| (goblin->localPosition.y < 0))
        {
            SPR_setVisibility(goblin->sprite, HIDDEN);
        }
        else
        {  
            if(!goblin->isDead)
            {
                SPR_setHFlip(goblin->sprite, goblin->flip);             
                SPR_setPosition(goblin->sprite, goblin->localPosition.x, goblin->localPosition.y);
                
                if(goblin->blink.En)
                {
                    goblinBlink(goblin);
                }
            
                SPR_setVisibility(goblin->sprite, goblin->blink.visibility);
                SPR_setAnim(goblin->sprite, goblin->states.animState);
            }
            else
            {
                SPR_setVisibility(goblin->sprite, VISIBLE);
                SPR_setPosition(goblin->sprite, goblin->localPosition.x, goblin->localPosition.y);
                SPR_setAnimationLoop(goblin->sprite, false);
                SPR_setAnim(goblin->sprite, goblin->states.animState);
            } 


        }
    }
}

GOBLIN_VISIBILITY_OFF_SCREEN
GOBLIN_VISIBILITY_ONSCREEN_LIVE_NORMAL
GOBLIN_VISIBILITY_ONSCREEN_LIVE_BLINK
GOBLIN_VISIBILITY_ONSCREEN_DEAD


void goblinAI(Goblin_Typedef *goblin)
{
    switch (goblin->states.aiState)
    {
        case AI_GOBLIN_ATTACK: goblinAI_Attack (goblin);   break;
        case AI_GOBLIN_DEATH:  goblinAI_Death  (goblin);   break;
        case AI_GOBLIN_TICKS:  goblinAI_Ticks  (goblin);   break;
        case AI_GOBLIN_IDLE:                               break;
    }    
}

void goblinAI_Attack(Goblin_Typedef *goblin)
{
    switch (goblin->states.attackState)
    {
        case GOBLIN_ATTACK_AIM:
            
            if(goblin->localPosition.x > 0 && goblin->localPosition.x < 300)
            {
                goblin->states.animState    = GOBLIN_ANIM_ATTACK;
                goblin->states.attackState  = GOBLIN_ATTACK_SHOOT;
                KDebug_Alert("GOBLIN THROW SPEAR START");
            }        

        break;

        case GOBLIN_ATTACK_SHOOT:

            if(goblin->sprite->frameInd == 5)
            {
               KDebug_Alert("GOBLIN CREATE SPEAR");
               goblin->createSpear(goblin);
               goblin->states.animState     = GOBLIN_ANIM_STAY;
               goblin->states.attackState   = GOBLIN_ATTACK_RELAX;
            }
                 
        break; 

        case GOBLIN_ATTACK_RELAX:

            goblin->states.aiState     = AI_GOBLIN_TICKS;

        break;           

        case GOBLIN_ATTACK_IDLE:       break;

    }
}

void goblinAI_Death(Goblin_Typedef *goblin)
{
    switch(goblin->states.deathState)
    {
        case GOBLIN_DEATH_START:

            goblin->states.deathState   = GOBLIN_DEATH_END;
            goblin->states.animState    = GOBLIN_ANIM_DEATH;
            goblin->states.aiState      = AI_GOBLIN_IDLE;

        break;

        case GOBLIN_DEATH_END:

        /*
            if(SPR_isAnimationDone(goblin->sprite))
            {
                SPR_setAnimationLoop(goblin->sprite, false);
            }        
        */


        break;        

    }


}

void goblinAI_Ticks(Goblin_Typedef *goblin)
{
    goblin->thinkTicksCnt--;
    if(goblin->thinkTicksCnt == 0) 
    {
        goblin->thinkTicksCnt       = goblin->thinkTicks;
        goblin->states.aiState      = AI_GOBLIN_ATTACK;
        goblin->states.attackState  = GOBLIN_ATTACK_AIM;
    }
}



