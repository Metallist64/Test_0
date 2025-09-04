
#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <genesis.h>
#include  "common.h"

typedef struct _collision_map
{
    uint16_t gridStep;
    uint16_t width;
    uint16_t hight;
    const uint8_t *data;    

}CollisionMap_Typedef;

uint8_t IsCollided(const CollisionMap_Typedef *map, Vec2_Typedef *position, RECT_Typedef *colRect);

#endif


