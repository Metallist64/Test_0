#include "collisions.h"
#include "common.h"
#include "player.h"
#include "level.h"
#include <genesis.h>
#include <kdebug.h>

char strDbg[64];

extern uint32_t flag;

uint16_t getCollision(Level_Typedef *level, Vec2_Typedef position, CollisionVec_Typedef collisionVector, uint16_t step)
{
    uint16_t        collisionFound      = false;
    uint16_t        noCollisionSteps    = false;
    Vec2_Typedef    checkVertex[2]      = { {0, 0}, {0, 0} };
    int16_t         operatorX            =  0;
    int16_t         operatorY            =  0;
    
    Vec2_Typedef vertexPlayer[4]    = {                                                                                  // CW order       
        { position.x + player.collisionRectOffset.x,                               position.y + player.collisionRectOffset.y },    // Rectangle vertex 0 
        { position.x + player.collisionRectOffset.x + player.collisionRect.right,  position.y + player.collisionRectOffset.y },    // Rectangle vertex 1
        { position.x + player.collisionRectOffset.x + player.collisionRect.right,  position.y + player.collisionRectOffset.y + player.collisionRect.bottom },    // Rectangle vertex 2
        { position.x + player.collisionRectOffset.x,                               position.y + player.collisionRectOffset.y + player.collisionRect.bottom },    // Rectangle vertex 3        
    };

     //KDebug_Alert("Collision type:"); 
     

    switch (collisionVector)
    {

        case COLLISION_VECTOR_NOT_USED:
        case COLLISION_VECTOR_LR:
        case COLLISION_VECTOR_ALL:
        
        break;

        case COLLISION_VECTOR_UP:
        
        break;

        case COLLISION_VECTOR_DOWN:     

            checkVertex[0].x = vertexPlayer[2].x;
            checkVertex[0].y = vertexPlayer[2].y;

            checkVertex[1].x = vertexPlayer[3].x;
            checkVertex[1].y = vertexPlayer[3].y;

            operatorX = 0;
            operatorY = 1;

        break;

        case COLLISION_VECTOR_RIGHT:    

            checkVertex[0].x = vertexPlayer[1].x;
            checkVertex[0].y = vertexPlayer[1].y;

            checkVertex[1].x = vertexPlayer[2].x;
            checkVertex[1].y = vertexPlayer[2].y;
            
            operatorX = 1;
            operatorY = 0;
            
        break;        

        case COLLISION_VECTOR_LEFT:  

            checkVertex[0].x = vertexPlayer[0].x;
            checkVertex[0].y = vertexPlayer[0].y;

            checkVertex[1].x = vertexPlayer[3].x;
            checkVertex[1].y = vertexPlayer[3].y;
            
            operatorX = -1;
            operatorY = 0;
            
        break;       
    }

    for(uint16_t tmp_step = 0; tmp_step < step; tmp_step++)
    {
        checkVertex[0].x += operatorX; checkVertex[0].y += operatorY;
        checkVertex[1].x += operatorX; checkVertex[1].y += operatorY; 

        collisionFound = getCollisionByPoint(level, checkVertex[0]);
        if(collisionFound == false)
        {
            collisionFound = getCollisionByPoint(level, checkVertex[1]);
        }
       
        if(collisionFound)
        {
            break;       
        }
        else
        {
            noCollisionSteps++;
        }
    }
   

    //KDebug_Alert("Collision rectangle:");
//    if(collisionVector == COLLISION_VECTOR_DOWN)  KDebug_AlertNumber(noCollisionSteps);    
    
    return noCollisionSteps;
}
 
uint16_t  getCollisionByPoint(pLevel_Typedef level, Vec2_Typedef point)
{
    //(vertex->y /map->gridStep) * map->width + vertex->x / map->gridStep;
    uint16_t            blockIdx    = (point.y /level->collisions->gridStep) * level->collisions->width + point.x / level->collisions->gridStep;     
    const uint8_t       blockData   = level->collisions->data[blockIdx];
    BlockInfo_Typedef   blockInfo   = blocksInfo[blockData];
    uint16_t            result      = blockInfo.collisionHandler(&blockInfo, &point);

    //if(collisionVector == COLLISION_VECTOR_DOWN) KDebug_Alert("pass ++");
    KDebug_AlertNumber(level->width);  
    //KDebug_AlertNumber(point.y);  
    //KDebug_AlertNumber(level->collisions->gridStep);  

    //while (1);
   

    return result;
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