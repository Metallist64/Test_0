#ifndef GOBLIN_H
#define GOBLIN_H

#include <genesis.h>
#include "common.h"


typedef enum  _goblin_animation  
{
    GOBLIN_ANIM_STAY,
    GOBLIN_ANIM_WALK,
    GOBLIN_ANIM_ATTACK,
    GOBLIN_ANIM_DUMMY_0,
    GOBLIN_ANIM_DEATH,
} GoblinAnim_Typedef;


typedef enum _goblin_state
{
    GOBLIN_THINK,
    GOBLIN_STAY,
    GOBLIN_WALK,
    GOBLIN_ATTACK,
    GOBLIN_DIE, 
} GoblinState_Typedef;

typedef enum _goblin_direction
{
    GOBLIN_DIR_FORWARD,     
    GOBLIN_DIR_BACKWARD,    
} GoblinDirection_Typedef;

typedef struct _goblin
{
    const SpriteDefinition  *spriteDef;     // RawSprite reference
    Sprite                  *sprite;        // Engine Sprite reference
    uint16_t                health; 
    GoblinDirection_Typedef direction;
    GoblinState_Typedef     state;    
    uint16_t                movement;
    Vec2_Typedef            globalPosition;
} Goblin_Typedef;

//extern Goblin_Typedef goblins[];

#endif