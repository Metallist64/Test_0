#include "collisions.h"
#include "common.h"
#include "player.h"
#include "level.h"
#include <genesis.h>
#include <kdebug.h>

char strDbg[64];

extern uint32_t flag;

CollisionInfo_Typedef getCollision(Level_Typedef *level, Vec2_Typedef position, CollisionVec_Typedef collisionVector, uint16_t step)
{
    CollisionInfo_Typedef result    = {0};
    
    Vec2_Typedef vertexPlayer[4]    = {                                                                                  // CW order       
        { position.x + player.collisionRectOffset.x,                               position.y + player.collisionRectOffset.y },    // Rectangle vertex 0 
        { position.x + player.collisionRectOffset.x + player.collisionRect.right,  position.y + player.collisionRectOffset.y },    // Rectangle vertex 1
        { position.x + player.collisionRectOffset.x + player.collisionRect.right,  position.y + player.collisionRectOffset.y + player.collisionRect.bottom },    // Rectangle vertex 2
        { position.x + player.collisionRectOffset.x,                               position.y + player.collisionRectOffset.y + player.collisionRect.bottom },    // Rectangle vertex 3        
    };

    Vec2_Typedef checkVertex[2] = { {0, 0}, {0, 0} };
    int16_t operator =  0;

    switch (collisionVector)
    {
        case COLLISION_VECTOR_UP:
        
        break;

        case COLLISION_VECTOR_DOWN:     

            checkVertex[0].x = vertexPlayer[2].x;
            checkVertex[0].y = vertexPlayer[2].y;

            checkVertex[1].x = vertexPlayer[3].x;
            checkVertex[1].y = vertexPlayer[3].y;

            operator = -1;

        break;

        case COLLISION_VECTOR_RIGHT:    

            checkVertex[0].x = vertexPlayer[1].x;
            checkVertex[0].y = vertexPlayer[1].y;

            checkVertex[1].x = vertexPlayer[2].x;
            checkVertex[1].y = vertexPlayer[2].y;
            
            operator = 1;
            
        break;        

        case COLLISION_VECTOR_LEFT:  

            checkVertex[0].x = vertexPlayer[0].x;
            checkVertex[0].y = vertexPlayer[0].y;

            checkVertex[1].x = vertexPlayer[3].x;
            checkVertex[1].y = vertexPlayer[3].y;
            
            operator = -1;
            
        break;       

        for(uint16_t tmp_step = 0; tmp_step < step; tmp_step++)
        {
            result.vertex[0] = getCollisionByPoint(level, checkVertex[0]);
            result.vertex[1] = getCollisionByPoint(level, checkVertex[1]);            
            
            checkVertex[0].x++; checkVertex[0].y++;
            checkVertex[1].x++; checkVertex[1].y++;            

            if(result.value)
            {
                break;       
            }
        }

    }

    //KDebug_Alert("Collision rectangle:");
    //KDebug_AlertNumber(vertex[0].x);    
    
    return result;
}
 
uint16_t  getCollisionByPoint(Level_Typedef *level, Vec2_Typedef point)
{
    uint16_t            blockIdx    = (point.y /level->collisions->gridStep) * level->width + point.x / level->collisions->gridStep;     
    const uint8_t       blockData   = level->collisions->data[blockIdx];
    BlockInfo_Typedef   blockInfo   = blocksInfo[blockIdx];
    uint16_t            result      = blockInfo.collisionHandler(&blockInfo, &point);

    return 0;
}


/*
CollisionType_Typedef getCollisionLeft(BlockInfoPack_Typedef *blocks_Info, uint16_t *vertex_Ypos)
{
    CollisionType_Typedef result = COLLISION_NOT_FOUND;

    if ((blocks_Info->data[0].collisionVectorMask & COLLISION_VECTOR_LEFT) && (vertex_Ypos[0] >= blocks_Info->data[0].groundLevel))
    {
        result = COLLISION_LEFT;     
    }
    else if ((blocks_Info->data[1].collisionVectorMask & COLLISION_VECTOR_LEFT) && (vertex_Ypos[1] >= blocks_Info->data[1].groundLevel))
    {
        result = COLLISION_LEFT;     
    }

    return result;     
}

CollisionType_Typedef getCollisionRight(BlockInfoPack_Typedef *blocks_Info, uint16_t *vertex_Ypos)
{
    CollisionType_Typedef result = COLLISION_NOT_FOUND;

    if ((blocks_Info->data[0].collisionVectorMask & COLLISION_VECTOR_RIGHT) && (vertex_Ypos[0] >= blocks_Info->data[0].groundLevel))
    {
        result = COLLISION_RIGHT;     
    }
    else if ((blocks_Info->data[1].collisionVectorMask & COLLISION_VECTOR_RIGHT) && (vertex_Ypos[1] >= blocks_Info->data[1].groundLevel))
    {
        result = COLLISION_RIGHT;     
    }

    return result;     
}


CollisionInfo_Typedef getCollisionDown(BlockInfoPack_Typedef *blocks_Info, uint16_t *vertex_Ypos, Vec2_Typedef position)
{
    CollisionInfo_Typedef result = {COLLISION_NOT_FOUND, 0, 0};

    if( (blocks_Info->data[0].collisionVectorMask & COLLISION_VECTOR_DOWN) && (vertex_Ypos[0] >= blocks_Info->data[0].groundLevel))
    {
            result.type = COLLISION_DOWN; 
            result.alignedPositionY = blocks_Info->data[0].groundLevel - vertex_Ypos[0] - 1 + position.y;
    }
    else if((blocks_Info->data[1].collisionVectorMask & COLLISION_VECTOR_DOWN) && (vertex_Ypos[1] >= blocks_Info->data[1].groundLevel))
        {
            result.type = COLLISION_DOWN;  
            result.alignedPositionY = blocks_Info->data[1].groundLevel - vertex_Ypos[1] - 1 + position.y;
        }            
    return result;            
}

*/

/*
CollisionInfo_Typedef getCollisionDown(BlockInfoPack_Typedef *blocks_Info, uint16_t *vertex_Ypos, Vec2_Typedef position)
{
    CollisionInfo_Typedef result = {COLLISION_NOT_FOUND, 0, 0};

    if( (blocks_Info->data[0].collisionVectorMask & COLLISION_VECTOR_DOWN) && (vertex_Ypos[0] >= blocks_Info->data[0].groundLevel))
    {
            result.type = COLLISION_DOWN; 
            result.alignedPositionY = blocks_Info->data[0].groundLevel - vertex_Ypos[0] - 1 + position.y;
    }
    else if((blocks_Info->data[1].collisionVectorMask & COLLISION_VECTOR_DOWN) && (vertex_Ypos[1] >= blocks_Info->data[1].groundLevel))
        {
            result.type = COLLISION_DOWN;  
            result.alignedPositionY = blocks_Info->data[1].groundLevel - vertex_Ypos[1] - 1 + position.y;
        }            
    return result;            
}


*/