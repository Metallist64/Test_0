#include <genesis.h>
#include <kdebug.h>

#include "common.h"

#ifndef PROJECTILE_H
#define PROJECTILE_H

#define MAX_PROJECTILES 8
#define SPEAR_Y_OFFSET  3

typedef struct _projectile
{
    const SpriteDefinition      *spriteDef;         // RawSprite reference
    Sprite                      *sprite;            // Engine Sprite reference
    int16_t                     velocityData[2];    // For Forward and Backward dierctions
    int16_t                     velocity;
    Vec2_Typedef                globalPosition;
    Vec2_Typedef                screenPosition;
    RECT_Typedef                collisionRect;
    uint16_t                    flip;
    void                        (*handler)(struct _projectile*);
} Projectile_Typedef;

typedef struct _projectiles
{
    Projectile_Typedef  items[MAX_PROJECTILES];

    void    (*handlesProcessing)  (void);

}Projectiles_Typedef;

extern Projectiles_Typedef    projectiles; 

uint16_t    createProjectileSpear   (Goblin_Typedef *goblin);

void    handlesProcessing       (void);
void    deleteProjectile        (Projectile_Typedef *projectile);
void    addProjectileSpearInfo  (Goblin_Typedef *goblin, Projectile_Typedef *spear);

void spearHandler   (Projectile_Typedef *spear);

#endif