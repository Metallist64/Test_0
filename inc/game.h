#ifndef GAME_H
#define GAME_H

#include "level.h"


typedef struct _game
{
    pLevel_Typedef  pCurrentLevel;
    uint16_t        lives;
    void            (*run)(void);
}Game_Typedef;

extern Game_Typedef game;

void gameProcessing(void);

#endif