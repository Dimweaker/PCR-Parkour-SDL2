#include <stdio.h>
#include "SDL2/SDL.h"
#include "parameter.h"
#include "SDL2/SDL_image.h"
#ifndef PARKOUR_PLAYER_ACTION_H
#define PARKOUR_PLAYER_ACTION_H
#define MAX_FRAMES 60
/* 玩家动作，用于存储玩家动作的帧数、位置、texture和surface */
typedef struct PlayerAction{
    int nums_of_frames; /* 动作的总帧数 */
    int current_frame; /* 当前帧 */
    SDL_Rect rect; /* 动作的位置 */
    SDL_Texture* texture[MAX_FRAMES];  /* 动作的texture */
    SDL_Surface* surface[MAX_FRAMES]; /* 动作的surface */
}PlayerAction;

PlayerAction* Create_Player_Action();
void Set_Player_Action_Texture(PlayerAction* action, SDL_Renderer* renderer);
void Set_Player_Action_Surface(PlayerAction* action, char* path_format);
void Destroy_Player_Action(PlayerAction* action);
void Draw_Player_Action(SDL_Renderer* renderer, PlayerAction* action);
#endif
