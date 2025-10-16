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
            SPR_setHFlip(goblin->sprite, goblin->flip);             
            SPR_setPosition(goblin->sprite, goblin->localPosition.x, goblin->localPosition.y);
            
            if(goblin->blink.En)
            {
               goblinBlink(goblin);
            }
        
            SPR_setVisibility(goblin->sprite, goblin->blink.visibility);
            SPR_setAnim(goblin->sprite, goblin->animState);
        }
    }
}


void goblinDeleteSpear(Goblin_Typedef *goblin)
{
    SPR_releaseSprite(goblin->spear->sprite);
    free(goblin->spear);
    goblin->spear = NULL;
}

GoblinSpear_Typedef *goblinCreateSpear(Goblin_Typedef *goblin)
{
    GoblinSpear_Typedef *spear = (GoblinSpear_Typedef*)malloc(sizeof(GoblinSpear_Typedef));
    if(spear == NULL) 
    {
        KDebug_Alert("Malloc error.");
        while (1);
    }
    else
    {
        if(goblin->flip == true)   spear->step = -1;
        else                       spear->step = 1;

        spear->globalPosition.x = goblin->globalPosition.x;
        spear->globalPosition.y = goblin->globalPosition.y + 3;
        spear->spriteDef = &orange_goblin_spear_sprite;
        spear->sprite = SPR_addSprite(spear->spriteDef, 0, 0, TILE_ATTR(PAL3, TRUE, FALSE, goblin->flip));

        SPR_setVisibility(spear->sprite, HIDDEN);
    }

    return spear;
}

void goblinAI(Goblin_Typedef *goblin)
{
    switch (goblin->stateAI)
    {
        case AI_GOBLIN_THINK:  goblinAI_Think  (goblin);   break;
        case AI_GOBLIN_WALK:   goblinAI_Walk   (goblin);   break;
        case AI_GOBLIN_ATTACK: goblinAI_Attack (goblin);   break;
        case AI_GOBLIN_STAY:   goblinAI_Stay   (goblin);   break;
        case AI_GOBLIN_DIE:    goblinAI_Die    (goblin);   break;
        case AI_GOBLIN_TICKS:  goblinAI_Ticks  (goblin);   break;
        case AI_GOBLIN_IDLE:                               break;
    }    
}

void goblinAI_Think(Goblin_Typedef *goblin)
{
    goblin->stateAI = AI_GOBLIN_ATTACK;
}

void goblinAI_Walk(Goblin_Typedef *goblin)
{
    goblin->stateAI = AI_GOBLIN_ATTACK;
}

void goblinAI_Attack(Goblin_Typedef *goblin)
{
    //KDebug_AlertNumber(goblin->attackState);

    switch (goblin->attackState)
    {
        case GOBLIN_ATTACK_AIM:
            
            if(goblin->localPosition.x > 0 && goblin->localPosition.x < 300)
            {
                goblin->animState = GOBLIN_ANIM_ATTACK;
                goblin->attackState = GOBLIN_ATTACK_THROW_SPEAR_START;
                KDebug_Alert("GOBLIN THROW SPEAR START");
            }        

        break;

        case GOBLIN_ATTACK_THROW_SPEAR_START:

            if(goblin->sprite->frameInd == 5)
            {
                KDebug_Alert("GOBLIN CREATE THROW");

                //SPR_setAnimAndFrame(goblin->sprite, GOBLIN_ANIM_WALK, 0);
                //SPR_setAnimationLoop(goblin->sprite, false);
                //SPR_setAutoAnimation(goblin->sprite, false);
                //SPR_setFrame(goblin->sprite, 6);
                goblin->animState = GOBLIN_ANIM_STAY;
                goblin->attackState = GOBLIN_ATTACK_THROW_SPEAR_PROCESSING;
            }
        break;        

        case GOBLIN_ATTACK_THROW_SPEAR_PROCESSING:

            //KDebug_AlertNumber( goblin->spear->globalPosition.x);
            goblin->spear->globalPosition.x += goblin->spear->step;
            int16_t spearLocalPositionX = goblin->spear->globalPosition.x - playerCamera.viewZone.left;
            int16_t spearLocalPositionY = goblin->spear->globalPosition.y - playerCamera.viewZone.top;

            //KDebug_Alert("Attack processing");

            if(spearLocalPositionX < 320 && spearLocalPositionX > 0)    SPR_setVisibility(goblin->spear->sprite, VISIBLE);
            else                                                        SPR_setVisibility(goblin->spear->sprite, HIDDEN);

            if(spearLocalPositionX < -32  || spearLocalPositionX > 320)
            {
                goblin->attackState = GOBLIN_ATTACK_THROW_SPEAR_END;
                KDebug_Alert("GOBLIN SPEAR INCORRECT POSITION-32 or > 320");
            }
            SPR_setPosition(goblin->spear->sprite, spearLocalPositionX, spearLocalPositionY); 

        break;          

        case GOBLIN_ATTACK_THROW_SPEAR_END:

            KDebug_Alert("GOBLIN DELETE THROW");
            goblinDeleteSpear(goblin);
            //SPR_setAnim(goblin->sprite, GOBLIN_ANIM_WALK);
//            SPR_setAnimAndFrame(goblin->sprite, GOBLIN_ANIM_WALK, 0);
            //SPR_setAutoAnimation(goblin->sprite, true);
            //SPR_setAnimationLoop(goblin->sprite, true);
            if(goblin->isDead)
            {
               goblin->stateAI      = AI_GOBLIN_IDLE;
               goblin->attackState  = GOBLIN_ATTACK_IDLE;
            }
            goblin->attackState = GOBLIN_ATTACK_AIM;
            //goblin->stateAI = AI_GOBLIN_WALK;

        break;           

        case GOBLIN_ATTACK_RELAX:

            //goblin->attackState = GOBLIN_ATTACK_AIM;
            //goblin->stateAI = GOBLIN_TICKS;

        break;       
        
        case GOBLIN_ATTACK_IDLE:

        break;

    }
}

void goblinAI_Stay(Goblin_Typedef *goblin)
{


}

void goblinAI_Die(Goblin_Typedef *goblin)
{
    if(SPR_isAnimationDone(goblin->sprite))
    {
        SPR_setAnimationLoop(goblin->sprite, false);
        goblin->stateAI = AI_GOBLIN_IDLE;
        //while(1)    ;
    }
}

void goblinAI_Ticks(Goblin_Typedef *goblin)
{
    goblin->thinkTicksCnt--;
    if(goblin->thinkTicksCnt == 0) 
    {
        goblin->thinkTicksCnt = goblin->thinkTicks;
        goblin->stateAI = AI_GOBLIN_ATTACK;
    }
}



