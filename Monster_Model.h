#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Rect_Queue.h"
#ifndef PARKOUR_MONSTER_MODEL_H
#define PARKOUR_MONSTER_MODEL_H
typedef struct MonsterModel{
    SDL_Rect rect;
    SDL_Texture* texture;
    SDL_Surface* surface;
}MonsterModel;

void Destroy_Monster_Model(MonsterModel* model);
void Draw_Monster_Model(SDL_Renderer* renderer, MonsterModel* model[], RectNode* node);

#endif
