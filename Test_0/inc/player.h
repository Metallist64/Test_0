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


typedef struct _player
{
    const SpriteDefinition  *spriteDef;     // RawSprite reference
    Sprite                  *sprite;        // Engine Sprite reference
    Vec2_Typedef            globalPosition;
    Vec2_Typedef            screenPosition;
    RECT_Typedef            collisionRect;
    //uint16_t                hight;
    uint16_t                relaxTimer;
    uint16_t                health;
}Player_Typedef;

extern Player_Typedef player;

void updatePlayerPosition(void);
void drawPlayer(void);

#endif