
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

typedef enum _block_type
{
    BLOCK_EMPTY     = 0,
    BLOCK_SOLID     = 1,
    BLOCK_SPIKE     = 2,
    BLOCK_TIMBER    = 3,

}BlockType_Typedef;

typedef struct block_info
{
    uint16_t            groundLevel;
    uint16_t            damage;
    BlockType_Typedef   type;

}BlockInfo_Typedef;

typedef struct block_info_pack
{
    BlockInfo_Typedef data[2];
}BlockInfoPack_Typedef;


typedef struct _collision_info
{
    CollisionType_Typedef   type;
    uint16_t                alignedPositionX;
    uint16_t                alignedPositionY;
    
}CollisionInfo_Typedef;

CollisionInfo_Typedef getCollision          (const CollisionMap_Typedef *map, Vec2_Typedef probePosition, CollisionVec_Typedef CollisionVector);
CollisionType_Typedef getCollisionLeftRight (BlockInfoPack_Typedef *blocks_Info, uint16_t *vertex_Ypos, CollisionType_Typedef collisionType);
CollisionInfo_Typedef getCollisionDown      (BlockInfoPack_Typedef *blocks_Info, uint16_t *vertex_Ypos, Vec2_Typedef position);
BlockInfo_Typedef     getBlockInfo          (const CollisionMap_Typedef *map, Vec2_Typedef *vertex);

#endif


