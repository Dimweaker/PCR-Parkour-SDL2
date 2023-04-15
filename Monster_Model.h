#include <stdio.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Rect_Queue.h"
#ifndef PARKOUR_MONSTER_MODEL_H
#define PARKOUR_MONSTER_MODEL_H
#define MAX_TYPE 3

/* 怪物模型，用于存储怪物的texture和surface */
typedef struct MonsterModel{
    SDL_Texture* texture[MAX_TYPE];
    SDL_Surface* surface[MAX_TYPE];
}MonsterModel;

void Destroy_Monster_Model(MonsterModel* model, int n);
void Draw_Monster_Model(SDL_Renderer* renderer, MonsterModel* model[], RectNode* node);
#endif
