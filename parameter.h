#include "SDL2/SDL.h"

#ifndef PARKOUR_PARAMETER_H
#define PARKOUR_PARAMETER_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FRAMES_RUN 24
#define FRAMES_JUMP 40
#define FRAMES_DIE 25
#define SCREEN_BPP 32
#define FPS 70
#define MONSTER_GROUND 0
#define MONSTER_AIR 1
#define MONSTER_GROUND_HEIGHT 100
#define MONSTER_GROUND_WIDTH 100
#define MONSTER_GROUND_Y 365
#define MONSTER_AIR_HEIGHT 100
#define MONSTER_AIR_WIDTH 100
#define MONSTER_AIR_Y 60
#define STATE_RUN 0
#define STATE_JUMP 1
#define STATE_DIE 2
#define NUMS_OF_STATE 3
#define NUMS_OF_MONSTER 2
#define AIR_TYPE 2
#define GROUND_TYPE 3
#define KARYL_RUN_PATH "images/run/run (%d).png"
#define KARYL_JUMP_PATH "images/jump/jump (%d).png"
#define KARYL_DIE_PATH "images/die/die (%d).png"
#define KARYL_RUN_RECT (SDL_Rect){20, 200, 250, 250}
#define KARYL_JUMP_RECT (SDL_Rect){40, 140, 250/0.8, 250/0.8}
#define KARYL_DIE_RECT (SDL_Rect){20, 200, 250, 250}
#define SCORE_RECT (SDL_Rect){450, 0, 0, 0}
#define TEXT_COLOR (SDL_Color){255, 51, 153, 255}
#define MONSTER_GROUND_PATH "images/monster/ground%d.png"
#define MONSTER_AIR_PATH "images/monster/air%d.png"
#define JUMP_HEIGHT(FRAME) (int)(12.5*FRAME - FRAME*FRAME/3.2)
#define SIGNAL_QUIT 0
#define SIGNAL_NEXT 1
#define SIGNAL_CONTINUE 2
#define SIGNAL_WAIT 3

#endif
