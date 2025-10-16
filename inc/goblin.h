#ifndef GOBLIN_H
#define GOBLIN_H

#include <genesis.h>
#include "common.h"

typedef enum  _goblin_animation  
{
    GOBLIN_ANIM_STAY = 0,
    GOBLIN_ANIM_WALK,
    GOBLIN_ANIM_ATTACK,
    GOBLIN_ANIM_DEATH = 4,
} GoblinAnim_Typedef;

typedef enum _goblin_state
{
    AI_GOBLIN_THINK,
    AI_GOBLIN_STAY,
    AI_GOBLIN_WALK,
    AI_GOBLIN_ATTACK,
    AI_GOBLIN_DIE, 
    AI_GOBLIN_TICKS,
    AI_GOBLIN_IDLE,
} GoblinStateAI_Typedef;

typedef enum _goblin_look
{
    GOBLIN_LOOK_FORWARD,     
    GOBLIN_LOOK_BACKWARD,    
} GoblinLookState_Typedef;

typedef enum _goblin_attack_state
{
    GOBLIN_ATTACK_AIM,     
    GOBLIN_ATTACK_THROW_SPEAR_START,     
    GOBLIN_ATTACK_THROW_SPEAR_PROCESSING,
    GOBLIN_ATTACK_THROW_SPEAR_END,
    GOBLIN_ATTACK_RELAX,    
    GOBLIN_ATTACK_IDLE,    
} GoblinAttackState_Typedef;

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

typedef struct _goblin_spear
{
    const SpriteDefinition  *spriteDef;     // RawSprite reference
    Sprite                  *sprite;        // Engine Sprite reference
    int16_t                 step;
    Vec2_Typedef            globalPosition;
    RECT_Typedef            collisionRect;
    uint16_t                thinkTicks;
    uint16_t                thinkTicksCnt;
    uint16_t                flip;
} ProjectileSpear_Typedef;

typedef struct _goblin
{
    const SpriteDefinition      *spriteDef;     // RawSprite reference
    Sprite                      *sprite;        // Engine Sprite reference
    uint16_t                    health; 
    GoblinStateAI_Typedef       stateAI;    
    uint16_t                    movement;
    Vec2_Typedef                globalPosition;
    Vec2_Typedef                localPosition;
    RECT_Typedef                collisionRect;
    uint16_t                    thinkTicks;
    uint16_t                    thinkTicksCnt;
    GoblinAnim_Typedef          animState;   
    uint16_t                    isDead;
    Path_Typdef                 path;
    uint16_t                    flip;
    BlinkState_Typdef           blink;
    GoblinAttackState_Typedef   attackState;
    GoblinLookState_Typedef     lookState;
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
void goblinAI_Think     (Goblin_Typedef *goblin);  
void goblinAI_Walk      (Goblin_Typedef *goblin);  
void goblinAI_Attack    (Goblin_Typedef *goblin);
void goblinAI_Stay      (Goblin_Typedef *goblin);  
void goblinAI_Die       (Goblin_Typedef *goblin);   
void goblinAI_Ticks     (Goblin_Typedef *goblin); 
void goblinAI_Idle      (Goblin_Typedef *goblin);  
void goblinDeleteSpear  (Goblin_Typedef *goblin);
void goblinBlink        (Goblin_Typedef *goblin);

GoblinSpear_Typedef *goblinCreateSpear(Goblin_Typedef *goblin);



#endif