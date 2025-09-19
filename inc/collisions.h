
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

typedef enum _collision_vector
{
    COLLISION_VECTOR_UP     = 0x01,
    COLLISION_VECTOR_DOWN   = 0x02,
    COLLISION_VECTOR_LEFT   = 0x04,
    COLLISION_VECTOR_RIGHT  = 0x08,
}CollisionVec_Typedef;

typedef enum _collision_type
{
    COLLISION_NOT_FOUND = 0x00,
    COLLISION_UP        = 0x01,
    COLLISION_DOWN      = 0x02,
    COLLISION_LEFT      = 0x04,
    COLLISION_RIGHT     = 0x08,
}CollisionType_Typedef;

CollisionType_Typedef getCollision(const CollisionMap_Typedef *map, CollisionVec_Typedef CollisionVector);

#endif


