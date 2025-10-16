#ifndef PLAYER_H
#define PLAYER_H

#include <genesis.h>
#include "level.h"
#include "collisions.h"
#include "common.h"



// Player state enumeration
typedef enum
{
    PLAYER_STAY,
    PLAYER_WALK,
    PLAYER_JUMP,
    PLAYER_ATTACK,
    PLAYER_ATTACK_2,
    PLAYER_DIE, 
} PlayerState_Typedef;


typedef enum _player_direction
{
    PLAYER_DIR_FORWARD = 0,     
    PLAYER_DIR_BACKWARD,    
} PlayerDirection_Typedef;

typedef enum  _player_animation  
{
    ANIM_STAY,
    ANIM_WALK,
    ANIM_ATTACK,
    ANIM_ATTACK_2,
    ANIM_KICK,
    ANIM_ATTACK_3,
    ANIM_JUMP,
    ANIM_SITBACK,
    ANIM_SIT_HI_ATACK,
    ANIM_FLY_ATACK,
    ANIM_PREY,
    ANIM_DUMMY_0,
    ANIM_DEATH,
    ANIM_WAKE,
    ANIM_SLEEP,
} PlayerAnim_Typedef;

typedef struct _attack
{
    uint16_t            attackIdx;                
    uint16_t            attackStateIdx[2];                
    PlayerState_Typedef attackState[2];
}Attack_Typedef;

typedef enum _player_jump_state
{
    JMP_AWAITING = 0,     
    JMP_GRAVITY,    
    JMP_RISE,     
    JMP_FALL,    
    JMP_AWAITING_RELEASE_BUTTON,
} JumpStage_Typedef;

typedef struct _player_jump
{
    JumpStage_Typedef   state;
    uint16_t            idx;
}Jump_Typedef;


typedef struct _input_word
{
    uint16_t            : 4;
    uint16_t    Mode    : 1;
    uint16_t    X       : 1;
    uint16_t    Y       : 1;
    uint16_t    Z       : 1;
    uint16_t    Start   : 1;
    uint16_t    A       : 1;
    uint16_t    C       : 1;
    uint16_t    B       : 1;
    uint16_t    Right   : 1;
    uint16_t    Left    : 1;
    uint16_t    Down    : 1;
    uint16_t    Up      : 1;
}InputWord_Typedef;


typedef union _input
{
    uint16_t            data;
    InputWord_Typedef   buttons;

}Input_Typedef;


typedef struct _player
{
    const SpriteDefinition  *spriteDef;     // RawSprite reference
    Sprite                  *sprite;        // Engine Sprite reference
    PlayerAnim_Typedef      animState;
    PlayerDirection_Typedef direction;
    Vec2_Typedef            globalPosition;
    Vec2_Typedef            screenPosition;
    RECT_Typedef            collisionRect;
    RECT_Typedef            attackCollisionRect[2];
    uint16_t                relaxTimer;
    uint16_t                health;
    Jump_Typedef            jump;
    PlayerState_Typedef     state;
    uint16_t                jumpPressed;
    Input_Typedef           input;
    uint16_t                gravity;
    uint16_t                movement;
    Attack_Typedef          attack;
    void                    (*init) (Level_Typedef*);
    
}Player_Typedef;

extern Player_Typedef player;

void        playerInit(Level_Typedef *level);
void        updatePlayerPosition(void);
void        playerGetButtons(void);
void        playerDraw(void);
void        playerJump(void);
void        playerMove(void);
void        playerAttack(void);
uint16_t    roundYposition(uint16_t);

#endif