
#ifndef LEVEL_H
#define LEVEL_H

#include <genesis.h>
#include "collisions.h"

typedef struct _level
{
    const char                  *name;
    const MapDefinition         *map;
    const TileSet               *tileSet;
    const Palette               *palette;
    const uint16_t              paletteBank;
    const uint16_t              width;
    const uint16_t              hight;
    Map                         *backgrounbd_A; //Forward
    Map                         *backgrounbd_B; //Backward
    const CollisionMap_Typedef  *collisions;
    const uint16_t              startX;
    const uint16_t              startY;
    const MapDefinition         *nextMap;
}Level_Typedef;

void loadLevel(Level_Typedef *level);

#endif