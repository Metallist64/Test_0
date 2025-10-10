#include <genesis.h>

#include "common.h"
#include "damage.h"



//void applyDamage

uint16_t checkBoxCollision (RECT_Typedef zone_0, RECT_Typedef zone_1)
{
    uint16_t result = false;

    Vec2_Typedef vertex[4] = 
    { 
        {zone_1.left,   zone_1.top}, 
        {zone_1.right,  zone_1.top}, 
        {zone_1.right,  zone_1.bottom},
        {zone_1.left,   zone_1.bottom},
    };

    for(uint16_t i = 0; i < 4; i++)
    {
        result += checkDamaeCollisionByPoint (zone_0, vertex[i]);
    }

    return result;
}


