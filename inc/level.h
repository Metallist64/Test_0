
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

typedef struct _block_info
{
    uint16_t                    groundLevel;
    uint16_t                    damage;
    uint16_t                    idx;
    CollisionVec_Typedef        collisionVectorMask;
    BlockType_Typedef           type;
    uint16_t                    (*collisionHandler)(struct _block_info*, Vec2_Typedef*);

}BlockInfo_Typedef;

void loadLevel(Level_Typedef *level);

CollisionInfo_Typedef   getCollision        (Level_Typedef *level, Vec2_Typedef position, CollisionVec_Typedef collisionVector, uint16_t step);
uint16_t                getCollisionByPoint (Level_Typedef *level, Vec2_Typedef point);

extern BlockInfo_Typedef blocksInfo[] ;

extern uint16_t EmptyBlockHandler   (BlockInfo_Typedef*, Vec2_Typedef*);
extern uint16_t SolidBlockHandler   (BlockInfo_Typedef*, Vec2_Typedef*);
extern uint16_t SpikeBlockHandler   (BlockInfo_Typedef*, Vec2_Typedef*);
extern uint16_t TimberBlockHandler  (BlockInfo_Typedef*, Vec2_Typedef*);
extern uint16_t ShelfBlockHandler   (BlockInfo_Typedef*, Vec2_Typedef*);



#endif