
#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <genesis.h>
#include  "common.h"
//#include  "level.h" - facking sucks

typedef struct _collision_map
{
    uint16_t        gridStep;
    uint16_t        width;
    uint16_t        hight;
    const uint8_t   *data;     

}CollisionMap_Typedef;

typedef enum _collision_vector
{
    COLLISION_VECTOR_NOT_USED   = 0x00,
    COLLISION_VECTOR_UP         = 0x01,
    COLLISION_VECTOR_DOWN       = 0x02,
    COLLISION_VECTOR_LEFT       = 0x04,
    COLLISION_VECTOR_LR         = 0x06,
    COLLISION_VECTOR_RIGHT      = 0x08,
    COLLISION_VECTOR_ALL        = 0x0F,

}CollisionVec_Typedef;

typedef enum _collision_type
{
    COLLISION_NOT_FOUND = 0x00,
    COLLISION_UP        = 0x01,
    COLLISION_DOWN      = 0x02,
    COLLISION_LEFT      = 0x04,
    COLLISION_RIGHT     = 0x08,

}CollisionType_Typedef;

typedef enum _block_type
{
    BLOCK_EMPTY     = 0,
    BLOCK_SOLID     = 1,
    BLOCK_SPIKE     = 2,
    BLOCK_TIMBER    = 3,
    BLOCK_SHELF     = 4,

}BlockType_Typedef;

typedef struct _collision_result
{
    uint16_t   successPasses;
    uint16_t   value;
    uint8_t    vertex[2];

}CollisionInfo_Typedef;

typedef struct _collisionBox
{
    Vec2_Typedef vertex[4];
    
}CollisionBox_Typedef;

CollisionBox_Typedef    createCollisionBox          (Vec2_Typedef position, RECT_Typedef collisionRect, Vec2_Typedef collisionRectOffset);
uint16_t                checkBoxCollision           (CollisionBox_Typedef zone_0, CollisionBox_Typedef zone_1);
uint16_t                checkCollisionBoxByPoint    (CollisionBox_Typedef box, Vec2_Typedef point);


#endif


