
#include "camera.h"
#include "common.h"
#include "level_0.h"
#include "player.h"
#include "kdebug.h"

Camera_Typedef playerCamera = 
{
	.viewZone.left		= 0,
	.viewZone.top		= 0,
	.viewZone.right		= SCREEN_WIDTH - 1,
	.viewZone.bottom	= SCREEN_HIGHT - 1,
	.focusZone.left		= OUTSIDE_AREA_WIDTH,
	.focusZone.top		= OUTSIDE_AREA_HIGHT,	
	.focusZone.right	= OUTSIDE_AREA_WIDTH + FOCUS_ZONE_WIDTH - 1,
	.focusZone.bottom	= OUTSIDE_AREA_HIGHT + FOCUS_ZONE_HIGHT - 1,
};

char str_debug[64];
char str_debug_2[64];

void updatePlayerCamera(void)
{
	RECT_Typedef focusZoneLimits		= {OUTSIDE_AREA_WIDTH, OUTSIDE_AREA_HIGHT, level_0.width - OUTSIDE_AREA_WIDTH, level_0.hight - OUTSIDE_AREA_HIGHT,};
	RECT_Typedef newFocusZone			= {playerCamera.focusZone.left, playerCamera.focusZone.top, playerCamera.focusZone.right, playerCamera.focusZone.bottom };

	if(player.globalPosition.x > playerCamera.focusZone.right)
	{
		newFocusZone.right = player.globalPosition.x;
		newFocusZone.left = newFocusZone.right - FOCUS_ZONE_WIDTH;
	}

	if(player.globalPosition.x < playerCamera.focusZone.left)
	{
		newFocusZone.left = player.globalPosition.x;
		newFocusZone.right = newFocusZone.left + FOCUS_ZONE_WIDTH;
	}	

	if(player.globalPosition.y < playerCamera.focusZone.top)
	{
		newFocusZone.top = player.globalPosition.y;
		newFocusZone.bottom = newFocusZone.top + FOCUS_ZONE_HIGHT;
	}	

	if(player.globalPosition.y > playerCamera.focusZone.bottom)
	{
		newFocusZone.bottom = player.globalPosition.y;
		newFocusZone.top = newFocusZone.bottom - FOCUS_ZONE_HIGHT;
	}
	//======================  Check limits for focuszone ========================
	if(newFocusZone.right > focusZoneLimits.right)
	{
		newFocusZone.right = focusZoneLimits.right;
		newFocusZone.left = newFocusZone.right - FOCUS_ZONE_WIDTH;	
	}

	if(newFocusZone.left < focusZoneLimits.left)
	{
		newFocusZone.left = focusZoneLimits.left;
		newFocusZone.right = newFocusZone.left + FOCUS_ZONE_WIDTH;
	}	

	if(newFocusZone.top < focusZoneLimits.top)
	{
		newFocusZone.top = focusZoneLimits.top;
		newFocusZone.bottom = newFocusZone.top + FOCUS_ZONE_HIGHT;	
	}	

	if(newFocusZone.bottom > focusZoneLimits.bottom)
	{
		newFocusZone.bottom = focusZoneLimits.bottom;
		newFocusZone.top = newFocusZone.bottom - FOCUS_ZONE_HIGHT;	
	}
	//===========================================================================
	//============================ Update camera zones ==========================		
	playerCamera.focusZone.left	= newFocusZone.left;	
	playerCamera.focusZone.top	= newFocusZone.top;
	playerCamera.focusZone.right	= newFocusZone.right;
	playerCamera.focusZone.bottom	= newFocusZone.bottom;
	
	playerCamera.viewZone.left	= newFocusZone.left 	- OUTSIDE_AREA_WIDTH;
	playerCamera.viewZone.top		= newFocusZone.top		- OUTSIDE_AREA_HIGHT;
	playerCamera.viewZone.right	= newFocusZone.right 	+ OUTSIDE_AREA_WIDTH;
	playerCamera.viewZone.bottom	= newFocusZone.bottom	+ OUTSIDE_AREA_HIGHT;
	//===========================================================================
	player.screenPosition.x = player.globalPosition.x - playerCamera.viewZone.left;
	player.screenPosition.y = player.globalPosition.y - playerCamera.viewZone.top;	

	KDebug_AlertNumber(newFocusZone.left);
	KDebug_AlertNumber(newFocusZone.right);
	//===========================================================================
	MAP_scrollTo(level_0.backgrounbd_A, playerCamera.viewZone.left, playerCamera.viewZone.top);
}
