  
#include "collisions.h"
#include "player.h"
#include "resources.h"

#include "level_0.h" // Not good !!! Fix!!! It must be something like game.h that included all levels!

#include <genesis.h>

#define ANIM_STAND          0
#define ANIM_WALK           1
#define ANIM_THROW          2
#define ANIM_STAND_2        3
#define ANIM_DIE            4


Player_Typedef player = 
{
    .spriteDef          = &player_sprite,
    .sprite             = NULL,
    .screenPosition.x   = 0,
    .screenPosition.y   = 0,    
    .globalPosition.x   = 0,
    .globalPosition.y   = 0,
    .collisionRect      = {0,0,16,16},
    .relaxTimer         = 10,
    .health             = 100
};

void updatePlayerPosition(void)
{
    Vec2_Typedef newPosition = {player.globalPosition.x, player.globalPosition.y};
    uint8_t collisionResult = false;
    uint16_t input = JOY_readJoypad(0);


    if((input & BUTTON_LEFT) == BUTTON_LEFT)      { if(newPosition.x > 0)       { newPosition.x--; } }
    if((input & BUTTON_RIGHT) == BUTTON_RIGHT)    { if(newPosition.x < 5000)   { newPosition.x++; } }
    if((input & BUTTON_UP)    == BUTTON_UP)       { if(newPosition.y > 0)      { newPosition.y--; } }
    if((input & BUTTON_DOWN)  == BUTTON_DOWN)     { if(newPosition.y < 800)     { newPosition.y++; } }
    
/*
    switch (input)
    {
        case BUTTON_LEFT:  if(newPosition.x > 0)      { newPosition.x--; };
        case BUTTON_RIGHT: if(newPosition.x < 5000)   { newPosition.x++; };
        case BUTTON_UP:    if(newPosition.y > 0)      { newPosition.y--; };
        case BUTTON_DOWN:  if(newPosition.y < 800)    { newPosition.y++; };        
        default:       break;
    }
*/
  
    collisionResult = IsCollided(level_0.collisions, &newPosition, &player.collisionRect);
    if(!collisionResult)
    {
        player.globalPosition.x = newPosition.x;
        player.globalPosition.y = newPosition.y;
    }   
}

void drawPlayer(void)
{


}

void updatePlayerAnimation(void)
{
    //if(player.)

}


void setSpritePosition(Sprite* sprite, s16 x, s16 y)
{
    // clip out of screen sprites
    if ((x < -100) || (x > 320) || (y < -100) || (y > 240)) SPR_setVisibility(sprite, HIDDEN);
    else
    {
        SPR_setVisibility(sprite, VISIBLE);
        SPR_setPosition(sprite, x, y);
    }
}

  void player12(void)
  {
    /*
    if(input == BUTTON_RIGHT)
            {
                if(++soniXpos < 320)
                {
                    SPR_setAnim(sonicObj.sprite, ANIM_WALK);
                    SPR_setHFlip(sonicObj.sprite, FALSE);
                    SPR_setPosition(sonicObj.sprite, soniXpos, soniYpos);       
                }
            } 

            if(input == BUTTON_LEFT)
            {
                if(--soniXpos > -48)
                {
                    SPR_setAnim(sonicObj.sprite, ANIM_WALK);
                    SPR_setHFlip(sonicObj.sprite, TRUE);
                    SPR_setPosition(sonicObj.sprite, soniXpos, soniYpos);       
                }   
            } 
                
        if(input == BUTTON_DOWN)
            {
                if(++soniYpos < 240)
                {
                    SPR_setAnim(sonicObj.sprite, ANIM_WALK);
                    SPR_setHFlip(sonicObj.sprite, TRUE);
                    SPR_setPosition(sonicObj.sprite, soniXpos, soniYpos);       
                }             
            } 

        if(input == BUTTON_UP)
            {
                if(--soniYpos > -48)
                {
                    SPR_setAnim(sonicObj.sprite, ANIM_WALK);
                    SPR_setHFlip(sonicObj.sprite, TRUE);
                    SPR_setPosition(sonicObj.sprite, soniXpos, soniYpos);       
                }             
            }    
            
        if(input == BUTTON_A)
            {
                SPR_setAnimationLoop(sonicObj.sprite, FALSE);
                SPR_setAnim(sonicObj.sprite, ANIM_DIE);

            }         
*/  
            //if (SPR_isAnimationDone(sonicObj->sprite))
    }