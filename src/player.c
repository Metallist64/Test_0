  
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
    .collisionRectOffset    = {20,16},
    .collisionRect          = {0,0,16,32},
    .relaxTimer             = 10,
    .health                 = 100,
    .state                  = 0,
    .jump.idx               = 0,
    .jump.state             = JMP_AWAITING,
};

const uint8_t jumpArray[] = {2,2,2,2,2,2,2,2,
                              2,2,2,2,2,2,2,2,
                              1,1,0,0,0,0,0,0};

uint16_t roundYposition(uint16_t position) //Bound
{
    uint16_t result = 0;
    uint16_t k = (position + 1) / 16;
    result = k * 16;

    return (result);
}

void playerJump(void)
{
    Vec2_Typedef newPosition = {player.globalPosition.x, player.globalPosition.y};
    CollisionType_Typedef collisionResult = COLLISION_NOT_FOUND;
    
     switch (player.jump.state)
     {

        case JMP_AWAITING_RELEASE_BUTTON:
            if(!player.input.buttons.A)
            {
                player.jump.state = JMP_AWAITING;
            }
        break;

        case JMP_AWAITING:

            if(player.input.buttons.A)
            {
                player.jump.state = JMP_RISE;
                player.jump.idx = 0;
                player.state = PLAYER_JUMP;
            }
            else 
            {
                player.jump.state = JMP_GRAVITY;
                player.state = PLAYER_STAY;
            }
            
        break;

        case JMP_GRAVITY:

            collisionResult = getCollision(level_0.collisions, COLLISION_VECTOR_DOWN);
            if(collisionResult != COLLISION_DOWN) 
            {
                newPosition.y++;
            }
            else
            {
                player.jump.state = JMP_AWAITING;
            }

        break;            

        case JMP_RISE:

            if(player.jump.idx < sizeof(jumpArray))
            {
               newPosition.y -= jumpArray[player.jump.idx];
               player.jump.idx++;
            }
            else
            {
                player.jump.state = JMP_FALL;    
                player.jump.idx = 0;
            }
            
        break;

        case JMP_FALL:

                newPosition.y += 2;
                //step can be > 2. And we can get inside collide block ! 14 + 2 = 16. Border = 15!
                // We can use round for newPosition (bounding)
                collisionResult = getCollision(level_0.collisions, COLLISION_VECTOR_DOWN);   
                if(collisionResult == COLLISION_DOWN)                   
                { 
                    newPosition.y = roundYposition(newPosition.y);
                    player.state = PLAYER_STAY;
                    player.jump.state = JMP_AWAITING_RELEASE_BUTTON; 
                }
        break;        
    }  
    player.globalPosition.y = newPosition.y;  
}

void playerMove(void)
{

    Vec2_Typedef newPosition = {player.globalPosition.x, player.globalPosition.y};
    CollisionType_Typedef collisionResult = COLLISION_NOT_FOUND;
    
   if(player.input.buttons.Right)
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
        if(player.state != PLAYER_JUMP) player.state = PLAYER_WALK;
    }  

    if(player.input.buttons.Left)
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
        if(player.state != PLAYER_JUMP) player.state = PLAYER_WALK;
    }     
    player.globalPosition.x = newPosition.x;
}

void playerDraw(void)
{
    switch (player.state)
    {
        case PLAYER_STAY:
            player.animState = ANIM_STAY;
        break;

        case PLAYER_WALK:
            player.animState = ANIM_WALK;
        break;        
        
        case PLAYER_JUMP:
            player.animState = ANIM_JUMP;
        break;
        
        case PLAYER_ATTACK:
            player.animState = ANIM_ATACK;
        break;

        case PLAYER_DIE:
            player.animState = ANIM_DEATH;
        break;        

        default:

            //player.animState = ANIM_STAY;

        break;
        }

    if(player.direction == PLAYER_DIR_FORWARD)  SPR_setHFlip(player.sprite, FALSE);
    else                                        SPR_setHFlip(player.sprite, TRUE);

    SPR_setPosition(player.sprite, player.screenPosition.x, player.screenPosition.y); 
    SPR_setAnim(player.sprite, player.animState);
}

//SPR_setAnimationLoop(sonicObj.sprite, FALSE);
//SPR_setAnim(sonicObj.sprite, ANIM_DIE);
//if (SPR_isAnimationDone(sonicObj->sprite))
//SPR_setVisibility(sprite, VISIBLE);


void playerGetButtons(void)
{
    player.input.data  = JOY_readJoypad(0);
}
