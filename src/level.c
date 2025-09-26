
#include <genesis.h>
#include "level.h"
#include "resources.h"
#include "player.h"


#define PLAYER_PALETTE PAL2
#define LEVEL_PALETTE PAL1
#define TILEMAP_PLANE BG_A

u16 VDPTilesFilled = TILE_USER_INDEX;
Map *backgroubd_A;

BlockProperties_Typedef getBlockProperties(BlockType_Typedef blockType)
{
	BlockProperties_Typedef result;

	switch (blockType)
	{
		case BLOCK_EMPTY:
				result.damage		= 0;
				result.topOffset	= 0;
		break;

		case BLOCK_SOLID:
				result.damage		= 0;
				result.topOffset	= 0;
		break;		
	
		case BLOCK_SPIKE:
				result.damage		= 15;
				result.topOffset	= 2;
		break;

		case BLOCK_TIMBER:
				result.damage		= 0;
				result.topOffset	= 7;
		break;		


	default:
		break;
	}

	return	result;

}


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
