#include <stdio.h>
#include "SDL2/SDL.h"
#include "parameter.h"
#include "SDL2/SDL_image.h"
#ifndef PARKOUR_PLAYER_ACTION_H
#define PARKOUR_PLAYER_ACTION_H
#define MAX_FRAMES 60
typedef struct PlayerAction{
    int nums_of_frames;
    int current_frame;
    SDL_Rect rect;
    SDL_Texture* texture[MAX_FRAMES];
    SDL_Surface* surface[MAX_FRAMES];
}PlayerAction;

PlayerAction* Create_Player_Action();
void Set_Player_Action_Texture(PlayerAction* action, SDL_Renderer* renderer);
void Set_Player_Action_Surface(PlayerAction* action, char* path_format);
void Destroy_Player_Action(PlayerAction* action);
void Draw_Player_Action(SDL_Renderer* renderer, PlayerAction* action);
#endif //PARKOUR_PLAYER_ACTION_H
