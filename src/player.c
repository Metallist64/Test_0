  
#include "collisions.h"
#include "player.h"
#include "resources.h"

#include "level_0.h" // Not good !!! Fix!!! It must be something like game.h that included all levels!

#include <genesis.h>
#include <kdebug.h>

Player_Typedef player = 
{
    .spriteDef              = &player_sprite,
    .sprite                 = NULL,
    .animState              = ANIM_STAY,
    .screenPosition         = {0,0},
    .globalPosition         = {0,0},
    .collisionRectOffset   =  {20,16},
    .collisionRect          = {0,0,16,32},
    .relaxTimer             = 10,
    .health                 = 100,
};

void updatePlayerPosition(void)
{
    //Vec2_Typedef newPosition = {player.globalPosition.x, player.globalPosition.y};
    //PlayerDirection_Typedef newDirection = PLAYER_DIR_FORWARD;
    CollisionType_Typedef collisionResult = COLLISION_NOT_FOUND;
    uint16_t input = JOY_readJoypad(0);

    /*
    if((input & BUTTON_LEFT) == BUTTON_LEFT)
    {
        if(newPosition.x > 0)
        {
            newPosition.x--; 
            player.direction = PLAYER_DIR_BACKWARD;
        } 
    }
    
    if((input & BUTTON_RIGHT) == BUTTON_RIGHT)
    {
        if(newPosition.x < 5000)
        {
            newPosition.x++; 
            player.direction = PLAYER_DIR_FORWARD;
        } 
    }    
    */

    collisionResult = getCollision(level_0.collisions, COLLISION_VECTOR_DOWN|COLLISION_VECTOR_UP);
    
    if(collisionResult != COLLISION_DOWN)
    {
        player.globalPosition.y++;
    }   
    else
    {
        //player.globalPosition.y = newPosition.y; 
        //KDebug_Alert("No collisions");
    }

    //player.globalPosition.x = newPosition.x;
    //player.globalPosition.y = newPosition.y;    


}

void drawPlayer(void)
{
    PlayerAnim_Typedef newAnimState = ANIM_STAY;

    switch (player.animState)
    {
        case ANIM_STAY:

            if(player.direction == PLAYER_DIR_FORWARD) SPR_setHFlip(player.sprite, FALSE);
            else SPR_setHFlip(player.sprite, TRUE);

            //SPR_setAnim(player.sprite, ANIM_WALK);

        break;
    
    default:
        break;
    }
    SPR_setPosition(player.sprite, player.screenPosition.x, player.screenPosition.y); 
    
    SPR_setAnim(player.sprite, 0);
    

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