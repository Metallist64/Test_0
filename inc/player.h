#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"
#include <genesis.h>

// Player state enumeration
typedef enum
{
    PLAYER_DIED,      // Player is dead/waiting to respawn
    PLAYER_OK,    // Player is alive and active
} PlayerState_Typedef;


typedef enum _player_direction
{
    PLAYER_DIR_FORWARD,     
    PLAYER_DIR_BACKWARD,    
} PlayerDirection_Typedef;

typedef enum    _player_animation  
{
    ANIM_STAY,
    ANIM_WALK,
    ANIM_ATACK,
    ANIM_ATACK_2,
    ANIM_JUMP,
    ANIM_SIT_LOW_ATACK,
    ANIM_SITBACK,
    ANIM_SIT_HI_ATACK,
    ANIM_FLY_ATACK,
    ANIM_PREY,
    ANIM_DUMMY_0,
    ANIM_DEATH,
    ANIM_WAKE,
    ANIM_SLEEP,
} PlayerAnim_Typedef;

typedef struct _player
{
    const SpriteDefinition  *spriteDef;     // RawSprite reference
    Sprite                  *sprite;        // Engine Sprite reference
    PlayerAnim_Typedef       animState;
    PlayerDirection_Typedef direction;
    Vec2_Typedef            globalPosition;
    Vec2_Typedef            screenPosition;
    Vec2_Typedef            collisionRectOffset;
    RECT_Typedef            collisionRect;
    uint16_t                relaxTimer;
    uint16_t                health;
    uint16_t                jump;

}Player_Typedef;

extern Player_Typedef player;

void updatePlayerPosition(void);
void drawPlayer(void);

#endif