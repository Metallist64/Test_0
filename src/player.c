  
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
    .collisionRectOffset    =  {20,16},
    .collisionRect          = {0,0,16,32},
    .relaxTimer             = 10,
    .health                 = 100,
    .jump.allow             = false,
    .jump.stage             = JMP_RISE,
    .jump.step              = 1,
    .jump.hight             = 0,    
    .jump.maxHight          = 100,
    .jump.fallSpeed         = 0,
    .jump.buttonReleased    = true,
    .state                  = 0,
};


void playerJump(void);                 

void updatePlayerPosition(void)
{
    /*
    
    
    Vec2_Typedef newPosition = {player.globalPosition.x, player.globalPosition.y};
    //PlayerDirection_Typedef newDirection = PLAYER_DIR_FORWARD;
    CollisionType_Typedef collisionResult = COLLISION_NOT_FOUND;
    uint16_t input = JOY_readJoypad(0);

    switch (player.state)
    {
        case 0:

            collisionResult = getCollision(level_0.collisions, COLLISION_VECTOR_DOWN);
            
            if((input & BUTTON_A) == BUTTON_A) player.state = 1;

        break;

        case 1:

            playerJump();

        break;        

        case 2:

            //playerWalk();
        
        break;    
      
    default:
        break;
    }

     
        
   
    if((input & BUTTON_A) == BUTTON_A)
    {
        if(player.jump.allow)
        {
            player.jump.allow = false;
            player.jump.try = true;
            player.jump.stage = JMP_RISE;
        }
        
    }

    if((input & BUTTON_RIGHT) == BUTTON_RIGHT)
    {
        if(newPosition.x < 5000)
        {
            collisionResult = getCollision(level_0.collisions, COLLISION_VECTOR_RIGHT);
            if(collisionResult != COLLISION_RIGHT)
            {
                newPosition.x++;       
            }
            player.direction = PLAYER_DIR_FORWARD;
        } 
    }  

    if((input & BUTTON_LEFT) == BUTTON_LEFT)
    {
        if(newPosition.x > 0)
        {
            collisionResult = getCollision(level_0.collisions, COLLISION_VECTOR_LEFT);
            if(collisionResult != COLLISION_LEFT)
            {
                newPosition.x--;       
            }
            player.direction = PLAYER_DIR_BACKWARD;
        } 
    } 

    else
    {
        //player.globalPosition.y = newPosition.y; 
        //KDebug_Alert("No collisions");
    }

    player.globalPosition.x = newPosition.x;
    player.globalPosition.y = newPosition.y;    
    */
}

uint16_t jumpIdx = 0; 


const uint16_t jumpArray[] = {2,2,2,2,2,2,2,2,
                              2,2,2,2,2,2,2,2,
                              1,1,0,0,0,0,0,0};


                              


uint16_t positionYRound(uint16_t position) //Bound
{
    uint16_t result = 0;
    uint16_t k = (position + 1) / 16;
    result = k * 16;

    return (result);

}

#define AWAITING_JUMP   0
#define JUMP_RISE       1
#define JUMP_FALL       2
#define GRAVITY         3

uint16_t jumpStage = AWAITING_JUMP; 

void playerJump(void)
{
    Vec2_Typedef newPosition = {player.globalPosition.x, player.globalPosition.y};
    CollisionType_Typedef collisionResult = COLLISION_NOT_FOUND;
    
    {   switch (jumpStage)
        {

            case AWAITING_JUMP:

                if(player.jumpPressed)
                {
                    jumpStage = JUMP_RISE;
                    jumpIdx = 0;
                }
                else 
                {
                    jumpStage = GRAVITY;
                }
                
            break;

            case GRAVITY:

                collisionResult = getCollision(level_0.collisions, COLLISION_VECTOR_DOWN);
                if(collisionResult != COLLISION_DOWN) 
                {
                    newPosition.y++;
                }
                else
                {
                    jumpStage = AWAITING_JUMP;
                }

            break;            

            case JUMP_RISE:

                if(jumpIdx < 24)
                {
                   newPosition.y -= jumpArray[jumpIdx];
                   kprintf("Jump Rise");

                   jumpIdx++;
                }
                else
                {
                    jumpStage = JUMP_FALL;    
                    jumpIdx = 0;
                }
                
            break;

            case JUMP_FALL:

                    newPosition.y += 2;
                    //step can be > 2. And we can get inside collide block ! 14 + 2 = 16. Border = 15!
                    // We can use round for newPosition (bounding)
                    collisionResult = getCollision(level_0.collisions, COLLISION_VECTOR_DOWN);   
                    if(collisionResult == COLLISION_DOWN)                   
                    { 
                        newPosition.y = positionYRound(newPosition.y);
                        jumpStage = AWAITING_JUMP; 
                    }
            break;        
        }  
    }
    //player.globalPosition.x = newPosition.x;
    player.globalPosition.y = newPosition.y;  
}

void playerMove(void)
{

    Vec2_Typedef newPosition = {player.globalPosition.x, player.globalPosition.y};
    uint16_t input = JOY_readJoypad(0);
     CollisionType_Typedef collisionResult = COLLISION_NOT_FOUND;
    
   if((input & BUTTON_RIGHT) == BUTTON_RIGHT)
    {
        if(newPosition.x < 5000)
        {
            collisionResult = getCollision(level_0.collisions, COLLISION_VECTOR_RIGHT);
            if(collisionResult != COLLISION_RIGHT)
            {
                newPosition.x++;       
            }



            player.direction = PLAYER_DIR_FORWARD;
        } 
    }  

    if((input & BUTTON_LEFT) == BUTTON_LEFT)
    {
        if(newPosition.x > 0)
        {
            collisionResult = getCollision(level_0.collisions, COLLISION_VECTOR_LEFT);
            if(collisionResult != COLLISION_LEFT)
            {
                newPosition.x--;       
            }
            player.direction = PLAYER_DIR_BACKWARD;
        } 
    }     

    player.globalPosition.x = newPosition.x;
    player.globalPosition.y = newPosition.y;  
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