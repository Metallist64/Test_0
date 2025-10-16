#include <genesis.h>
#include <kdebug.h>

#include "common.h"

#ifndef PROJECTILE_H
#define PROJECTILE_H

#define MAX_SPEARS  8

typedef struct _projectile
{
    const SpriteDefinition      *spriteDef;         // RawSprite reference
    Sprite                      *sprite;            // Engine Sprite reference
    int16_t                     velocity;
    Vec2_Typedef                globalPosition;
    Vec2_Typedef                screenPosition;
    RECT_Typedef                collisionRect;
    uint16_t                    flip;
    struct _projectile_spear    *next;
    void                        (*handler)(struct _projectile*);
} Projectile_Typedef;

typedef struct _projectile_queue
{
    Projectile_Typedef  projectile[8];
    uint16_t            num;

}ProjectileQueue_Typedef;


typedef struct _rojectiles
{
    ProjectileQueue_Typedef  spears;      

    void    (*checkCollisions)  (ProjectileQueue_Typedef*);
    void    (*draw)             (ProjectileQueue_Typedef*);

}ProjectilesQueue_Typedef;




void projectilesDraw(void);

#endif