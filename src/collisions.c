#include "collisions.h"
#include "common.h"
#include "player.h"
#include "level.h"
#include <genesis.h>
#include <kdebug.h>

char strDbg[64];

CollisionType_Typedef getCollision(const CollisionMap_Typedef *map, CollisionVec_Typedef CollisionVector)
{
    
    uint16_t                    blockTopOffset      = 0;
    BlockProperties_Typedef     blockProperties     = {0,0};
    CollisionType_Typedef       result              = COLLISION_NOT_FOUND;
    CollisionBlockInfo_Typedef  collisionBlockInfo  = {0, BLOCK_EMPTY};


    Vec2_Typedef vertex[4] = {                                                                                  // CW order       
        { player.globalPosition.x + player.collisionRectOffset.x,                                  player.globalPosition.y + player.collisionRectOffset.y },    // Rectangle vertex 0 
        { player.globalPosition.x + player.collisionRectOffset.x + player.collisionRect.right - 1, player.globalPosition.y + player.collisionRectOffset.y },    // Rectangle vertex 1
        { player.globalPosition.x + player.collisionRectOffset.x + player.collisionRect.right - 1, player.globalPosition.y + player.collisionRectOffset.y + player.collisionRect.bottom - 1 },    // Rectangle vertex 2
        { player.globalPosition.x + player.collisionRectOffset.x,                                  player.globalPosition.y + player.collisionRectOffset.y + player.collisionRect.bottom - 1 },    // Rectangle vertex 3        
    };

    switch (CollisionVector)
    {
        case COLLISION_VECTOR_UP:
        
        break;
        
        case COLLISION_VECTOR_DOWN:     //Using block properties to get top offset for timber, spikes and other complex tile
            vertex[2].y += 1;
            vertex[3].y += 1;

            collisionBlockInfo = getCollisionBlockInfo(map, &vertex[2]);

            if(collisionBlockInfo.type != BLOCK_EMPTY)
            {
                blockTopOffset = vertex[2].y % map->gridStep;
                blockProperties = getBlockProperties(collisionBlockInfo.type);
                if(blockTopOffset == blockProperties.topOffset)
                {
                    //KDebug_Alert("Collision down.");
                    result = COLLISION_DOWN;    
                }
            }
            else
            {
                collisionBlockInfo = getCollisionBlockInfo(map, &vertex[3]);
                
                if(collisionBlockInfo.type != BLOCK_EMPTY)
                {
                    blockTopOffset = vertex[3].y % map->gridStep;
                    blockProperties = getBlockProperties(collisionBlockInfo.type);
                    if(blockTopOffset == blockProperties.topOffset)
                    {
                        //KDebug_Alert("Collision down.");
                        result = COLLISION_DOWN;    
                    }
                }
            }
        break;

        case COLLISION_VECTOR_LEFT:
            vertex[0].x -= 1;
            vertex[3].x -= 1;        

            collisionBlockInfo = getCollisionBlockInfo(map, &vertex[0]);
            if(collisionBlockInfo.type == BLOCK_SOLID)
            {
                //KDebug_Alert("Collision left.");
                result = COLLISION_LEFT;
            }
            else
            {
                collisionBlockInfo = getCollisionBlockInfo(map, &vertex[3]);
                if(collisionBlockInfo.type == BLOCK_SOLID)
                {
                    //KDebug_Alert("Collision left.");
                    result = COLLISION_LEFT;
                }
            }
        break;        

        case COLLISION_VECTOR_RIGHT:
            vertex[1].x += 1;
            vertex[2].x += 1;      

            collisionBlockInfo = getCollisionBlockInfo(map, &vertex[1]);
            if(collisionBlockInfo.type == BLOCK_SOLID)
            {
                //KDebug_Alert("Collision left.");
                result = COLLISION_RIGHT;
            }
            else
            {
                collisionBlockInfo = getCollisionBlockInfo(map, &vertex[2]);
                if(collisionBlockInfo.type == BLOCK_SOLID)
                {
                    //KDebug_Alert("Collision left.");
                    result = COLLISION_RIGHT;
                }
            }
        break;        
    
        default:

        break;
    }

    //KDebug_Alert("Collision rectangle:");
    //KDebug_AlertNumber(vertex[0].x);    
    
    return result;
}
 

CollisionBlockInfo_Typedef getCollisionBlockInfo(const CollisionMap_Typedef *map, Vec2_Typedef *vertex)
{
    CollisionBlockInfo_Typedef colblockinfo = {0};

    colblockinfo.idx    = (vertex->y /map->gridStep) * map->width + vertex->x / map->gridStep;         
    colblockinfo.type   = map->data[colblockinfo.idx];

    return colblockinfo;
}