  
#include <genesis.h>
#include <kdebug.h>
#include "collisions.h"
#include "player.h"
#include "resources.h"

#include "level_0.h" 
#include "game.h" 

Player_Typedef player = 
{
    .spriteDef                  = &player_sprite,
    .sprite                     = NULL,
    .animState                  = ANIM_STAY,
    .screenPosition             = {0, 0},
    .globalPosition             = {0, 0},
    .collisionRectOffset        = {22, 15},
    .collisionRect              = {0, 0, 16, 32},

    .attackCollisionRectOffset  = {32, 15},    
    .attackCollisionRect        = {0, 0, 16, 32},

    .relaxTimer             = 10,
    .health                 = 100,
    .state                  = 0,
    .jump.idx               = 0,
    .jump.state             = JMP_AWAITING,
    .gravity                = 2,    
    .movement               = 1,
    .attack                 = { 0, {1, 0}, {PLAYER_ATTACK, PLAYER_ATTACK_2}},
    .init                   = playerInit,
};

const uint8_t jumpArray[] = {   2,2,2,2,2,2,2,2,
                                2,2,2,2,2,2,2,2,
                                1,1,0,0,0,0,0,0};


void playerInit(Level_Typedef *level)
{
    player.globalPosition.x = level->startX;
    player.globalPosition.y = level->startY;
    player.sprite = SPR_addSprite(player.spriteDef, player.globalPosition.x, player.globalPosition.y, TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
    SPR_setAnim(player.sprite, ANIM_STAY);
    //KDebug_Alert("Player position:");
    //KDebug_AlertNumber(player.attack.attackIdx); 
    //KDebug_AlertNumber(player.attack.attackIdx); 
}
  

void playerAttack(void)
{
    switch (player.state)
    {
        case PLAYER_STAY:
        case PLAYER_WALK:

            if(player.input.buttons.C)
            {
                player.attack.attackIdx = player.attack.attackStateIdx[player.attack.attackIdx];
                player.state = player.attack.attackState[player.attack.attackIdx];
                //KDebug_AlertNumber(player.attack.attackIdx); 
                //KDebug_Alert("Attack");
            }

        break;

        case PLAYER_ATTACK:
        case PLAYER_ATTACK_2:
            
            if((player.sprite->frameInd == 2) || (player.sprite->frameInd == 3))
            {
                //check attack collision
            }   
            //KDebug_AlertNumber(player.sprite->frameInd); 

            if (SPR_isAnimationDone(player.sprite))
            {
                player.state = PLAYER_STAY;       
            }

        break;

        default:
        
        break;

    }
}

uint32_t flag = 0;

void playerJump(void)
{
    Vec2_Typedef            newPosition         = {player.globalPosition.x, player.globalPosition.y};
    uint16_t                noCollisionsSteps   = 0; 
    
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
                if((player.state != PLAYER_ATTACK) && (player.state != PLAYER_ATTACK_2))
                {
                    player.state = PLAYER_STAY;                    
                }
            }
            
        break;

        case JMP_GRAVITY:

            noCollisionsSteps = getCollision(game.currentLevel, newPosition, COLLISION_VECTOR_DOWN, player.gravity);
            newPosition.y += noCollisionsSteps;
            if(noCollisionsSteps == 0)
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
                
                noCollisionsSteps = getCollision(game.currentLevel, newPosition, COLLISION_VECTOR_DOWN, player.gravity);
                newPosition.y += noCollisionsSteps;
                if(noCollisionsSteps == 0)
                {
                    player.state = PLAYER_STAY;
                    player.jump.state = JMP_AWAITING_RELEASE_BUTTON; 
                }

        break;        
    }  
    player.globalPosition.y = newPosition.y;  
}

void playerMove(void)
{
    Vec2_Typedef            newPosition         = {player.globalPosition.x, player.globalPosition.y};
    uint16_t                noCollisionsSteps   = 0;    
    
    if((player.input.buttons.Right) && (player.state != PLAYER_ATTACK))
    {
        if(newPosition.x < 5728)
        {
            noCollisionsSteps = getCollision(game.currentLevel, newPosition, COLLISION_VECTOR_RIGHT, player.movement);
            newPosition.x += noCollisionsSteps;
            player.direction = PLAYER_DIR_FORWARD;
            if(player.state != PLAYER_JUMP) player.state = PLAYER_WALK;        
        } 
    }  

    if((player.input.buttons.Left) && (player.state != PLAYER_ATTACK))
    {
        if(newPosition.x > 0)
        {
            noCollisionsSteps = getCollision(game.currentLevel, newPosition, COLLISION_VECTOR_LEFT, player.movement);
            newPosition.x -= noCollisionsSteps;     
            player.direction = PLAYER_DIR_BACKWARD;
            if(player.state != PLAYER_JUMP) player.state = PLAYER_WALK;        
        } 
    }     
    player.globalPosition.x = newPosition.x;
}

void playerDraw(void)
{
    switch (player.state)
    {
        case PLAYER_STAY:       player.animState = ANIM_STAY;       break;
        case PLAYER_WALK:       player.animState = ANIM_WALK;       break;        
        case PLAYER_JUMP:       player.animState = ANIM_JUMP;       break;
        case PLAYER_ATTACK:     player.animState = ANIM_ATTACK;     break;        
        case PLAYER_ATTACK_2:   player.animState = ANIM_ATTACK_2;   break;        
        case PLAYER_DIE:        player.animState = ANIM_DEATH;      break;        

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
