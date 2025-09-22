#include "collisions.h"
#include "common.h"
#include "player.h"
#include <genesis.h>
#include <kdebug.h>

char strDbg[64];

CollisionType_Typedef getCollision(const CollisionMap_Typedef *map, CollisionVec_Typedef CollisionVector)
{
    uint16_t blockIdx               = 0;
    //uint8_t blockColided            = 0;
    uint8_t tmp                     = 0;
    CollisionType_Typedef result    = COLLISION_NOT_FOUND;

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
        
        case COLLISION_VECTOR_DOWN:
            vertex[2].y += 1;
            vertex[3].y += 1;
            // Check vertex 2
            blockIdx = (vertex[2].y /map->gridStep) * map->width + vertex[2].x / map->gridStep;
            tmp = *(map->data + blockIdx);

            // Check vertex 3
            blockIdx = (vertex[3].y /map->gridStep) * map->width + vertex[3].x / map->gridStep;
            tmp += *(map->data + blockIdx);

            if(tmp)
            {
                //KDebug_Alert("Collision down.");
                result = COLLISION_DOWN;
            }

        break;

        case COLLISION_VECTOR_LEFT:
            vertex[0].x -= 1;
            vertex[3].x -= 1;        

            // Check vertex 2
            blockIdx = (vertex[0].y /map->gridStep) * map->width + vertex[0].x / map->gridStep;
            tmp = *(map->data + blockIdx);

            // Check vertex 3
            blockIdx = (vertex[3].y /map->gridStep) * map->width + vertex[3].x / map->gridStep;
            tmp += *(map->data + blockIdx);

            if(tmp)
            {
                KDebug_Alert("Collision left.");
                result = COLLISION_LEFT;
            } 
        break;        

        case COLLISION_VECTOR_RIGHT:
            vertex[1].x += 1;
            vertex[2].x += 1;      

            // Check vertex 2
            blockIdx = (vertex[1].y /map->gridStep) * map->width + vertex[1].x / map->gridStep;
            tmp = *(map->data + blockIdx);

            // Check vertex 3
            blockIdx = (vertex[2].y /map->gridStep) * map->width + vertex[2].x / map->gridStep;
            tmp += *(map->data + blockIdx);

            if(tmp)
            {
                KDebug_Alert("Collision right.");
                result = COLLISION_RIGHT;
            }            
            
            //result = COLLISION_RIGHT;
        break;        
    
    default:

        break;
    }

    //KDebug_Alert("Collision rectangle:");
    //KDebug_AlertNumber(vertex[0].x);    

    /*
    for(uint16_t i = 0; i < 4; i++)
    {
            blockIdx = (vertex[i].y /map->gridStep) * map->width + vertex[i].x / map->gridStep;
            blockColided = *(map->data + blockIdx);
            if(blockColided)
            {
                KDebug_Alert("Collision detected.");
                result = true;
                //result |= (1 << i);
            }
    }     
    */

    
    return result;
}
 