
#include <genesis.h>
//#include <kdebug.h>
#include "camera.h"
#include "level.h"
#include "level_0.h"
#include "resources.h"
#include "player.h"
#include "game.h"

typedef enum
{
    GAME_INTRO,      // Player is dead/waiting to respawn
    GAME_START,    // Player is alive and active
    GAME_RUN,
    GAME_PAUSE,
    GAME_OVER,
} GameState_Typedef;

const TileSet *tile_anim[] =
    {
        &animated_tileset_frame_0,
    };

s16 frameTicks;
s16 tileFrameIndex;
#define TILE_FRAMES_NUM             1
#define TILE_FRAME_DELAY            10
#define  TILE_DST    5

void TilesAnimationUpdate()
{
    /*
    
    */
    if (frameTicks-- == 0)
    {
        // reset frame counter
        frameTicks = TILE_FRAME_DELAY;
        
        // increase frame index
        tileFrameIndex++;
        
        // reset frame index to 0 if reached last frame + 1
        if (tileFrameIndex == TILE_FRAMES_NUM)
            tileFrameIndex = 0;
        
        // load next frame of animated tileset to beginning of VRAM map aria
        //VDP_loadTileSet(tile_anim[tileFrameIndex], level_0.backgrounbd_A->baseTile, DMA);
    }
    //0 - plane B
     VDP_loadTileSet(tile_anim[0], TILE_USER_INDEX + TILE_DST, DMA);
}    



Pool *objectPoolExplosin;
char str_0[64];
char str_1[64];
char str_2[64];


uint8_t blocNum = 0;
int main(bool hardReset)
{
    if (!hardReset)
        SYS_hardReset();
    
    // Set resolution to 320 x 224
    VDP_setScreenWidth320();
    //Init sprite engine
    SPR_init();
    //Set palette for text messages
    VDP_setTextPalette(PAL0);
    loadLevel(&level_0);
    

    PAL_setPalette(PAL2, player_sprite.palette->data, DMA);

    KDebug_Alert ("Game started");

    player.sprite = SPR_addSprite(player.spriteDef, 0, player.globalPosition.y, TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
    SPR_setAnim(player.sprite, ANIM_STAY);

    //TilesAnimationUpdate();
     
    VDP_loadTileSet(tile_anim[0], TILE_USER_INDEX + TILE_DST, DMA);

    while(1)
    {
        game.run();
       
        
        
        sprintf(str_0, "Camera X,Y = %04d, %04d", playerCamera.viewZone.left, playerCamera.viewZone.top);
        sprintf(str_1, "Position X,Y = %04d, %04d", player.globalPosition.x, player.globalPosition.y);
        sprintf(str_2, "Player state = %05d", player.state);

        VDP_drawTextBG(BG_B, str_0, 0, 0);
        VDP_drawTextBG(BG_B, str_1, 0, 1);
        VDP_drawTextBG(BG_B, str_2, 0, 2);
        
        SPR_update();
        SYS_doVBlankProcess();
    }

    return 0;
}

// Main game loop - updates all game systems each frame

