
#include <genesis.h>
#include <kdebug.h>
#include "camera.h"
#include "level.h"
#include "level_0.h"
#include "resources.h"
#include "player.h"


typedef enum
{
    GAME_INTRO,      // Player is dead/waiting to respawn
    GAME_START,    // Player is alive and active
    GAME_RUN,
    GAME_PAUSE,
    GAME_OVER,
} GameState_Typedef;


Pool *objectPoolExplosin;
char str_0[64];
char str_1[64];


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
    
    while(1)
    {
        updatePlayerPosition();     //Update player global position
        updatePlayerCamera();       //Calculate player screen position from global position on current map
        drawPlayer();
        
        
        
        SPR_setPosition(player.sprite, player.screenPosition.x, player.screenPosition.y); 


        sprintf(str_0, "Camera X,Y = %04d, %04d", playerCamera.viewZone.left, playerCamera.viewZone.top);
        sprintf(str_1, "Position X,Y = %04d, %04d", player.globalPosition.x, player.globalPosition.y);
        //sprintf(str_0, "Position X,Y,Block = %03d, %03d, %03d", STEP_AREA_WIDTH, STEP_AREA_HIGHT, blocNum);

        VDP_drawTextBG(BG_B, str_0, 0, 0);
        VDP_drawTextBG(BG_B, str_1, 0, 1);
        
        SPR_update();
        SYS_doVBlankProcess();
    }

    return 0;
}

// Main game loop - updates all game systems each frame

