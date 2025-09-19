#ifndef COMMON_H
#define COMMON_H

#include <genesis.h>

#define SCREEN_WIDTH    320
#define SCREEN_HIGHT    224

typedef struct _vec2
{
    int16_t     x; 
    int16_t     y;
}Vec2_Typedef;

typedef struct _rect
{
    int16_t     left; 
    int16_t     top; 
    int16_t     right;
    int16_t     bottom;
}RECT_Typedef;

#endif