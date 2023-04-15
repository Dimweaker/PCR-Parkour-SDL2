#include "parameter.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <stdio.h>
#ifndef PARKOUR_SCORE_H
#define PARKOUR_SCORE_H
/* 分数，用于存储分数的值、texture和surface */
typedef struct Score {
    int score;
    SDL_Texture *texture;
    SDL_Surface *surface;
}Score;
Score* InitScore();
void DestroyScore(Score* score);
void DrawScore(SDL_Renderer* renderer, Score* score, TTF_Font* font, SDL_Color color);
#endif
