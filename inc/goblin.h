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
    GOBLIN_IDLE,
    GOBLIN_TICKS,
} GoblinState_Typedef;

typedef enum _goblin_direction
{
    GOBLIN_MOVE_STAY,     
    GOBLIN_MOVE_FORWARD,     
    GOBLIN_MOVE_BACKWARD,    
} GoblinMoveState_Typedef;

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

typedef struct _goblin
{
    const SpriteDefinition  *spriteDef;     // RawSprite reference
    Sprite                  *sprite;        // Engine Sprite reference
    uint16_t                health; 
    GoblinMoveState_Typedef moveSatate;
    GoblinState_Typedef     stateAI;    
    uint16_t                movement;
    Vec2_Typedef            globalPosition;
    RECT_Typedef            collisionRect;
    Vec2_Typedef            collisionRectOffset;    
    uint16_t                thinkTicks;
    uint16_t                thinkTicksCnt;
    GoblinAnim_Typedef      animState;   
    uint16_t                isDead;
    Path_Typdef             path;
    uint16_t                flip;
    BlinkState_Typdef       blink;

} Goblin_Typedef;

typedef struct _goblins_list
{
    Goblin_Typedef  *list; 
    uint16_t        cnt;

}GoblinsList_Typedef;

void goblinsInit    (GoblinsList_Typedef    *goblinsList);
void goblinsAI      (GoblinsList_Typedef    *goblinsList);
void goblinAI       (Goblin_Typedef         *goblin);
void goblinsDraw    (GoblinsList_Typedef    *goblinsList);

void goblinAI_Think (Goblin_Typedef *goblin);  
void goblinAI_Walk  (Goblin_Typedef *goblin);  
void goblinAI_Attack(Goblin_Typedef *goblin);
void goblinAI_Stay  (Goblin_Typedef *goblin);  
void goblinAI_Die   (Goblin_Typedef *goblin);   
void goblinAI_Ticks (Goblin_Typedef *goblin); 
void goblinAI_Idle  (Goblin_Typedef *goblin);  

#endif