#include "collisions.h"
#include "common.h"
#include "player.h"
#include "level.h"
#include <genesis.h>
#include <kdebug.h>

char strDbg[64];

extern uint32_t flag;

CollisionType_Typedef getCollision(const CollisionMap_Typedef *map, CollisionVec_Typedef CollisionVector)
{

    CollisionType_Typedef   result      = COLLISION_NOT_FOUND;
    BlockInfo_Typedef       block_0_Info   = {0}, 
                            block_1_Info   = {0}, 
                            blockInfo      = {0};
    
    uint16_t                vertex_0_TopOffset = 0xffff, // Top Offset in block
                            vertex_1_TopOffset = 0xffff,
                            vertexTopOffset    = 0xffff;
    
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
            
            block_0_Info =  getBlockInfo (map, &vertex[2]);
            block_1_Info =  getBlockInfo (map, &vertex[3]);
            vertex_0_TopOffset = vertex[2].y % map->gridStep;
            vertex_1_TopOffset = vertex[3].y % map->gridStep;            

            if(block_0_Info.type != BLOCK_EMPTY)
            {
                if(vertex_0_TopOffset >= block_0_Info.topCollisionOffset)
                {
                    result = COLLISION_DOWN; 
                    //KDebug_AlertNumber(vertex_0_TopOffset);                                
                    //KDebug_AlertNumber(block_0_Info.topCollisionOffset); 
                    //if(flag == 1) while(1);            
                }
            }

            if(block_1_Info.type != BLOCK_EMPTY)
            {
                if(vertex_1_TopOffset >= block_1_Info.topCollisionOffset)
                {
                    result = COLLISION_DOWN;                        
                }
            }              
            /*
            blockInfo =  getBlockInfo (map, &vertex[2]);
            if(blockInfo.type != BLOCK_EMPTY)
            {
                vertexTopOffset = vertex[2].y % map->gridStep;
            }
            else
            {
                blockInfo =  getBlockInfo (map, &vertex[3]);
                if(blockInfo.type != BLOCK_EMPTY)
                {
                    vertexTopOffset = vertex[3].y % map->gridStep;
                }
            }

            if(vertexTopOffset == blockInfo.topCollisionOffset)
            {
                        //KDebug_Alert("Collision down.");
                        //KDebug_AlertNumber(blockInfo.type);  
                        result = COLLISION_DOWN;    
            }
            */


        break;

        case COLLISION_VECTOR_LEFT:
            vertex[0].x -= 1;
            vertex[3].x -= 1;        

            block_0_Info =  getBlockInfo (map, &vertex[0]);
            block_1_Info =  getBlockInfo (map, &vertex[3]);
            vertex_0_TopOffset = vertex[0].y % map->gridStep;
            vertex_1_TopOffset = vertex[3].y % map->gridStep;

            if(block_0_Info.type != BLOCK_EMPTY)
            {
                if(vertex_0_TopOffset >= block_0_Info.topCollisionOffset)
                {
                    result = COLLISION_LEFT;                        
                }
            }

            if(block_1_Info.type != BLOCK_EMPTY)
            {
                if(vertex_1_TopOffset >= block_1_Info.topCollisionOffset)
                {
                    result = COLLISION_LEFT;                        
                }
            }          

        break;        

        case COLLISION_VECTOR_RIGHT:

            vertex[1].x += 1;
            vertex[2].x += 1;      
            block_0_Info =  getBlockInfo (map, &vertex[1]);
            block_1_Info =  getBlockInfo (map, &vertex[2]);
            vertex_0_TopOffset = vertex[1].y % map->gridStep;
            vertex_1_TopOffset = vertex[2].y % map->gridStep;

            if(block_0_Info.type != BLOCK_EMPTY)
            {
                if(vertex_0_TopOffset >= block_0_Info.topCollisionOffset)
                {
                    result = COLLISION_RIGHT;                        
                }
            }

            if(block_1_Info.type != BLOCK_EMPTY)
            {
                if(vertex_1_TopOffset >= block_1_Info.topCollisionOffset)
                {
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
 

BlockInfo_Typedef getBlockInfo (const CollisionMap_Typedef *map, Vec2_Typedef *vertex)
{
    BlockInfo_Typedef   blockInfo   = {0};
    uint16_t            idx         = (vertex->y /map->gridStep) * map->width + vertex->x / map->gridStep;     
    BlockType_Typedef   blockType   = (BlockType_Typedef)map->data[idx];

    switch(blockType)
    {
        case BLOCK_EMPTY:
			blockInfo.damage		        = 0;
			blockInfo.topCollisionOffset    = 0;
            blockInfo.type                  = BLOCK_EMPTY;
		break;

		case BLOCK_SOLID:
			blockInfo.damage		        = 0;
			blockInfo.topCollisionOffset	= 0;
            blockInfo.type                  = BLOCK_SOLID;
		break;		
	
		case BLOCK_SPIKE:
			blockInfo.damage		        = 15;
			blockInfo.topCollisionOffset	= 2;
            blockInfo.type                  = BLOCK_SPIKE;
		break;

		case BLOCK_TIMBER:
			blockInfo.damage		        = 0;
			blockInfo.topCollisionOffset	= 8;
            blockInfo.type                  = BLOCK_TIMBER;
		break;		


	    default:

		break;

    }
    
    return blockInfo;
}
