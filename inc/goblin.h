#ifndef GOBLIN_H
#define GOBLIN_H

#include <genesis.h>
#include "common.h"

typedef enum  _goblin_animation_state  
{
    GOBLIN_ANIM_STAY = 0,
    GOBLIN_ANIM_WALK,
    GOBLIN_ANIM_ATTACK,
    GOBLIN_ANIM_DEATH = 4,
} GoblinAnimState_Typedef;

typedef enum _goblin_ai_state
{
    AI_GOBLIN_ATTACK,
    AI_GOBLIN_DEATH, 
    AI_GOBLIN_TICKS,
    AI_GOBLIN_IDLE,
} GoblinAiState_Typedef;

typedef enum _goblin_attack_state
{
    GOBLIN_ATTACK_AIM,     
    GOBLIN_ATTACK_SHOOT,     
    GOBLIN_ATTACK_RELAX,    
    GOBLIN_ATTACK_IDLE,    
} GoblinAttackState_Typedef;

typedef enum _goblin_death_state
{
    GOBLIN_DEATH_START,     
    GOBLIN_DEATH_END,     
} GoblinDeathState_Typedef;

typedef struct _goblin_states
{
    GoblinAiState_Typedef       aiState;
    GoblinAttackState_Typedef   attackState;
    GoblinDeathState_Typedef    deathState;
    GoblinAnimState_Typedef     animState;
}GoblinStates_Typedef;

typedef struct _path
{
    uint16_t start;
    uint16_t end;
}Path_Typdef;

typedef struct _blink
{
    uint16_t                En;
    SpriteVisibility        visibility;
    uint16_t                ticks;
    uint16_t                ticksCnt;
    uint16_t                period;
    uint16_t                periodCnt;
}BlinkState_Typdef;

typedef enum _goblin_look
{
    GOBLIN_LOOK_FORWARD,     
    GOBLIN_LOOK_BACKWARD,    
} GoblinLookState_Typedef;


typedef struct _goblin
{
    const SpriteDefinition      *spriteDef;     // RawSprite reference
    Sprite                      *sprite;        // Engine Sprite reference
    uint16_t                    health; 
    GoblinStates_Typedef        states;    
    uint16_t                    movement;
    Vec2_Typedef                globalPosition;
    Vec2_Typedef                localPosition;
    RECT_Typedef                collisionRect;
    uint16_t                    thinkTicks;
    uint16_t                    thinkTicksCnt;
    uint16_t                    isDead;
    Path_Typdef                 path;
    uint16_t                    flip;
    BlinkState_Typdef           blink;
    GoblinLookState_Typedef     lookState;
    uint16_t                    (*createSpear)(struct _goblin*);
} Goblin_Typedef;


typedef struct _goblins_list
{
    Goblin_Typedef  *list; 
    uint16_t        cnt;

}GoblinsList_Typedef;

void goblinsInit        (GoblinsList_Typedef    *goblinsList);
void goblinsAI          (GoblinsList_Typedef    *goblinsList);
void goblinAI           (Goblin_Typedef         *goblin);
void goblinsDraw        (GoblinsList_Typedef    *goblinsList);
void goblinAI_Attack    (Goblin_Typedef *goblin);
void goblinAI_Stay      (Goblin_Typedef *goblin);  
void goblinAI_Death     (Goblin_Typedef *goblin);   
void goblinAI_Ticks     (Goblin_Typedef *goblin); 
void goblinAI_Idle      (Goblin_Typedef *goblin);  
void goblinDeleteSpear  (Goblin_Typedef *goblin);
void goblinBlink        (Goblin_Typedef *goblin);

#endif