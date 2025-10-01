#include "collisions.h"
#include "common.h"
#include "player.h"
#include "level.h"
#include <genesis.h>
#include <kdebug.h>

char strDbg[64];

extern uint32_t flag;

CollisionInfo_Typedef getCollision(const CollisionMap_Typedef *map, Vec2_Typedef position, CollisionVec_Typedef CollisionVector)
{

    CollisionInfo_Typedef   result          = {COLLISION_NOT_FOUND, 0, 0};
    BlockInfoPack_Typedef   blocks_Info     = {
                                                .data[0] = {0, 0, COLLISION_VECTOR_NOT_USED},
                                                .data[1] = {0, 0, COLLISION_VECTOR_NOT_USED},                                                    
                                              }; 
    uint16_t                vertex_Ypos[2]  = {0xffff, 0xffff};
    
    Vec2_Typedef vertex[4] = {                                                                                  // CW order       
        { position.x + player.collisionRectOffset.x,                               position.y + player.collisionRectOffset.y },    // Rectangle vertex 0 
        { position.x + player.collisionRectOffset.x + player.collisionRect.right,  position.y + player.collisionRectOffset.y },    // Rectangle vertex 1
        { position.x + player.collisionRectOffset.x + player.collisionRect.right,  position.y + player.collisionRectOffset.y + player.collisionRect.bottom },    // Rectangle vertex 2
        { position.x + player.collisionRectOffset.x,                               position.y + player.collisionRectOffset.y + player.collisionRect.bottom },    // Rectangle vertex 3        
    };

    switch (CollisionVector)
    {
        case COLLISION_VECTOR_UP:
        
        break;
        
        case COLLISION_VECTOR_DOWN:     //Using block properties to get top offset for timber, spikes and other complex tile
            vertex[2].y += 1;
            vertex[3].y += 1;
            
            blocks_Info.data[0] = getBlockInfo (map, &vertex[2]);
            blocks_Info.data[1] = getBlockInfo (map, &vertex[3]);

            vertex_Ypos[0]  = vertex[2].y % map->gridStep;
            vertex_Ypos[1]  = vertex[3].y % map->gridStep;     

            result = getCollisionDown(&blocks_Info, vertex_Ypos, position);

        break;

        case COLLISION_VECTOR_RIGHT:

            vertex[1].x += 1;
            vertex[2].x += 1;      

            blocks_Info.data[0] = getBlockInfo (map, &vertex[1]);
            blocks_Info.data[1] = getBlockInfo (map, &vertex[2]);
            vertex_Ypos[0]      = vertex[1].y % map->gridStep;
            vertex_Ypos[1]      = vertex[2].y % map->gridStep;

            result.type = getCollisionRight(&blocks_Info, vertex_Ypos);

        break;        

        case COLLISION_VECTOR_LEFT:

            vertex[0].x -= 1;
            vertex[3].x -= 1;        

            blocks_Info.data[0] = getBlockInfo (map, &vertex[0]);
            blocks_Info.data[1] = getBlockInfo (map, &vertex[3]);
            vertex_Ypos[0]      = vertex[0].y % map->gridStep;
            vertex_Ypos[1]      = vertex[3].y % map->gridStep;
             
            result.type = getCollisionLeft(&blocks_Info, vertex_Ypos);

        break;        
    
        default:

        break;
    }

    //KDebug_Alert("Collision rectangle:");
    //KDebug_AlertNumber(vertex[0].x);    
    
    return result;
}
 

BlockInfo_Typedef getBlockInfo (const CollisionMap_Typedef *map, Vec2_Typedef *vertex)
{
    BlockInfo_Typedef   blockInfo   = {0};
    uint16_t            idx         = (vertex->y /map->gridStep) * map->width + vertex->x / map->gridStep;     
    BlockType_Typedef   blockType   = (BlockType_Typedef)map->data[idx];

    switch(blockType)
    {
        case BLOCK_EMPTY:
			blockInfo.damage		        = 0;
			blockInfo.groundLevel           = 0;
            blockInfo.collisionVectorMask   = COLLISION_VECTOR_NOT_USED;
		break;

		case BLOCK_SOLID:
			blockInfo.damage		        = 0;
			blockInfo.groundLevel	        = 0;
            blockInfo.collisionVectorMask   = COLLISION_VECTOR_ALL;
		break;		
	
		case BLOCK_SPIKE:
			blockInfo.damage		        = 15;
			blockInfo.groundLevel	        = 14;
            blockInfo.collisionVectorMask   = COLLISION_VECTOR_DOWN;
		break;

		case BLOCK_TIMBER:
			blockInfo.damage		        = 0;
			blockInfo.groundLevel	        = 8;
            blockInfo.collisionVectorMask   = COLLISION_VECTOR_ALL;
		break;		

		case BLOCK_SHELF:
			blockInfo.damage		        = 0;
			blockInfo.groundLevel	        = 0;
            blockInfo.collisionVectorMask   = COLLISION_VECTOR_DOWN;
		break;		        

	    default:

		break;

    }
    
    return blockInfo;
}

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


/*
CollisionType_Typedef getCollisionLeftRight(BlockInfoPack_Typedef *blocks_Info, uint16_t *vertex_Ypos, CollisionType_Typedef collisionType)
{
    CollisionType_Typedef result = COLLISION_NOT_FOUND;

    if(vertex_Ypos[0] >= blocks_Info->data[0].groundLevel)
    {
    KDebug_Alert("Collision right vertex 0");
    KDebug_AlertNumber(vertex_Ypos[0]);          
    KDebug_AlertNumber(vertex_Ypos[1]);          
        result = collisionType;     
        while(1);
    }
    else if(vertex_Ypos[1] >= blocks_Info->data[1].groundLevel)
         {   
    KDebug_Alert("Collision right vertex 1");
    KDebug_AlertNumber(vertex_Ypos[1]);              
            result  = collisionType;                        
         }
    return result;     
}
*/