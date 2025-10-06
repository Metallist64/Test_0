
#include <genesis.h>
#include <kdebug.h>
#include "level.h"
#include "resources.h"
#include "player.h"


#define PLAYER_PALETTE PAL2
#define LEVEL_PALETTE PAL1
#define TILEMAP_PLANE BG_A

u16 VDPTilesFilled = TILE_USER_INDEX;
//Map *backgroubd_A;


BlockInfo_Typedef blocksInfo[] = {

    {
        .damage		    	= 0,
        .groundLevel    	= 0,
        .type           	= BLOCK_EMPTY,
		.collisionHandler	= EmptyBlockHandler,
    },

    {
        .damage		    	= 0,
        .groundLevel    	= 0,
        .type           	= BLOCK_SOLID,
		.collisionHandler	= SolidBlockHandler,
    },

    {
        .damage		    	= 15,
        .groundLevel    	= 14,
        .type           	= BLOCK_SPIKE,
		.collisionHandler	= SpikeBlockHandler,
    },

    {
        .damage		    	= 0,
        .groundLevel    	= 8,
        .type           	= BLOCK_TIMBER,
		.collisionHandler	= TimberBlockHandler,
    },

    {
        .damage		    	= 0,
        .groundLevel    	= 0,
        .type           	= BLOCK_SHELF,
		.collisionHandler	= ShelfBlockHandler,
    },

};

uint16_t EmptyBlockHandler   (BlockInfo_Typedef *block, Vec2_Typedef* point)
{
	uint16_t result = false;

	return result;
};

uint16_t SolidBlockHandler   (BlockInfo_Typedef *block, Vec2_Typedef* point)
{
	uint16_t result = true;
	
	return result;
};

uint16_t SpikeBlockHandler   (BlockInfo_Typedef *block, Vec2_Typedef* point)
{
	uint16_t result = true;
	
	return result;
};

uint16_t TimberBlockHandler  (BlockInfo_Typedef *block, Vec2_Typedef* point)
{
	uint16_t result = true;
	//(vertex_Ypos[1] >= blocks_Info->data[1].groundLevel)
	//vertex_Ypos[1]  = vertex[3].y % map->gridStep;     
	return result;
};

uint16_t ShelfBlockHandler   (BlockInfo_Typedef *block, Vec2_Typedef* point)
{
	uint16_t result = true;
	
	return result;
};


void loadLevel(Level_Typedef *level)
{
	//Setup the level background with the MAP tool from SGDK
	PAL_setPalette(level->paletteBank, level->palette->data, CPU);
	//Load tiles into VRAM
	VDP_loadTileSet(level->tileSet, VDPTilesFilled, CPU);
	//Create map for 
	level->backgrounbd_A = MAP_create(level->map, TILEMAP_PLANE, TILE_ATTR_FULL(LEVEL_PALETTE, FALSE, FALSE, FALSE, VDPTilesFilled));

    player.globalPosition.x = level->startX;
    player.globalPosition.y = level->startY;

	
	//Update the number of tiles filled in order to avoid overlaping them when loading more
	//VDPTilesFilled += level_tileset.numTile;

	//We need to call this function at some point, this place seems to be a good one for doing it
	//generateCollisionMap(collisionMap);

	//Start play the level's song
	//XGM_startPlay(song);
}
