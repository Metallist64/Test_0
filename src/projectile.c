
#include <genesis.h>
#include <kdebug.h>

#include "camera.h"
#include "common.h"
#include "goblin.h"
#include "projectile.h"
#include "resources.h"

Projectiles_Typedef    projectiles =
{
    .handlesProcessing = handlesProcessing,    

};  

//==================================================== Spear ====================================================

Projectile_Typedef defaultSpear = 
{
    .spriteDef      = NULL,         
    .sprite         = NULL,            
    .velocityData   = {2, -2},
    .velocity       = 0,
    .globalPosition = {0, 0},
    .screenPosition = {0, 0},
    .collisionRect  = {0, 0, 32, 16},
    .flip           = false,
    .handler        = spearHandler,   

};

void handlesProcessing (void)
{
    uint16_t idx = 0;
    //uint16_t 

    for(; idx < MAX_PROJECTILES; idx++)
    {
        if(projectiles.items[idx].handler)
        {
            projectiles.items[idx].handler(&projectiles.items[idx]);                
        }
    }
}

void spearHandler(Projectile_Typedef *spear)
{
    spear->globalPosition.x += spear->velocity;
    spear->screenPosition.x  = spear->globalPosition.x - playerCamera.viewZone.left;
    spear->screenPosition.y  = spear->globalPosition.y - playerCamera.viewZone.top;

    if(spear->screenPosition.x > 320 || spear->screenPosition.x  < -32 || spear->screenPosition.y > 224 || spear->screenPosition.y  < - 32) 
    {
        SPR_setVisibility(spear->sprite, HIDDEN);
        KDebug_AlertNumber((uint32_t)spear->handler);
        deleteProjectile(spear);
        KDebug_Alert("SPEAR DELETE");
        KDebug_AlertNumber((uint32_t)spear->handler);
    }
    else
    {
        SPR_setPosition(spear->sprite, spear->screenPosition.x, spear->screenPosition.y);       
    }
}

void addProjectileSpearInfo(Goblin_Typedef *goblin, Projectile_Typedef *spear)
{
    memcpy(spear, &defaultSpear, sizeof(Projectile_Typedef));
    spear->spriteDef        = &orange_goblin_spear_sprite;
    spear->flip             = goblin->flip;
    spear->velocity         = spear->velocityData[spear->flip];
    spear->globalPosition.x = goblin->globalPosition.x;
    spear->globalPosition.y = goblin->globalPosition.y + SPEAR_Y_OFFSET;
    spear->sprite           = SPR_addSprite(spear->spriteDef, 0, 0, TILE_ATTR(PAL3, TRUE, FALSE, spear->flip));
    SPR_setVisibility(spear->sprite, VISIBLE);    
}

uint16_t createProjectileSpear(Goblin_Typedef *goblin)
{
    uint16_t    result  = false;

    for(uint16_t idx = 0; idx < MAX_PROJECTILES && result == false; idx++)
    {
        if (projectiles.items[idx].handler == NULL)
        {
            addProjectileSpearInfo(goblin, &projectiles.items[idx]);
            result = true;    
        }
    }
    return result;
}

void deleteProjectile(Projectile_Typedef *projectile)
{
    SPR_releaseSprite(projectile->sprite);
    projectile->handler = NULL;
}
//===============================================================================================================
