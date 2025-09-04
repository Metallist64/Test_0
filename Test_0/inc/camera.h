#ifndef MAP_H
#define MAP_H

#define FOCUS_ZONE_WIDTH		40	//Must even 2
#define FOCUS_ZONE_HIGHT		40	//Must even 2

#define OUTSIDE_AREA_WIDTH	((SCREEN_WIDTH - FOCUS_ZONE_WIDTH) / 2)
#define OUTSIDE_AREA_HIGHT 	((SCREEN_HIGHT - FOCUS_ZONE_HIGHT) / 2)

#include "common.h"
#include "level.h"
#include <genesis.h>

typedef struct _camera
{
    RECT_Typedef    viewZone;
    RECT_Typedef    focusZone;
}Camera_Typedef;

extern Camera_Typedef playerCamera;

void updatePlayerCamera(void);


#endif


/*  
                            320 x 244
*********************************************************************
*                                                                   *
*                         OUSIDE_AREA_HIGHT                         *
*                                                                   *       
*                       **********************                      *    
*                       * FOCUS_ZONE_WIDTH   *                      *            
*  OUSIDE_AREA_WIDTH    *        x           * OUSIDE_AREA_WIDTH    *
*                       * FOCUS_ZONE_HIGHT   *                      *
*                       **********************                      *
*                                                                   *
*                         OUSIDE_AREA_HIGHT                         *        
*                                                                   *    
*********************************************************************                        

*/