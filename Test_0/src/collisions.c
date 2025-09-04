#include "collisions.h"
#include "common.h"
#include <genesis.h>
#include <kdebug.h>

char strDbg[64];

uint8_t IsCollided(const CollisionMap_Typedef *map, Vec2_Typedef *position, RECT_Typedef *colRect)
{
    uint16_t blockIdx       = 0;
    uint8_t blockColided    = 0;
    uint8_t result          = 0;
    
    Vec2_Typedef vertex[4] = {                                                      // CW order       
        { position->x,                      position->y                       },    // Rectangle vertex 0 
        { position->x + colRect->right - 1, position->y                       },    // Rectangle vertex 1
        { position->x + colRect->right - 1, position->y + colRect->bottom - 1 },    // Rectangle vertex 2
        { position->x,                      position->y + colRect->bottom - 1 },    // Rectangle vertex 3        
    };
   
    KDebug_Alert("Collision rectangle:");
    KDebug_AlertNumber(vertex[0].x);
    KDebug_AlertNumber(vertex[0].y);

    KDebug_AlertNumber(vertex[1].x);
    KDebug_AlertNumber(vertex[1].y);

    KDebug_AlertNumber(vertex[2].x);
    KDebug_AlertNumber(vertex[2].y);

    KDebug_AlertNumber(vertex[3].x);
    KDebug_AlertNumber(vertex[3].y); 
    


    // Check all vertexes for collision. If any vertexes collided - just break cycle
   for(uint16_t i = 0; i < 4; i++)
   {
        blockIdx = (vertex[i].y /map->gridStep) * map->width + vertex[i].x / map->gridStep;
        blockColided = *(map->data + blockIdx);
        if(blockColided)
        {
            result = blockColided;
            break;
        }
   } 
    
    return result;
}
 