#include "score.h"

/**
 * 初始化分数
 * @return Score结构体指针
 */
Score* InitScore(){
    Score* score = (Score*)malloc(sizeof(Score));
    score->score = 0;
    score->surface = NULL;
    score->texture = NULL;
    return score;
}

/**
 * 销毁分Score结构体
 * @param score Score结构体指针
 */
void DestroyScore(Score* score){
    SDL_FreeSurface(score->surface);
    SDL_DestroyTexture(score->texture);
    free(score);
}

/**
 * 绘制分数
 * @param renderer 窗口的渲染器
 * @param score Score结构体指针
 * @param font 字体
 * @param color 颜色
 */
void DrawScore(SDL_Renderer* renderer, Score* score, TTF_Font* font, SDL_Color color){
    char score_str[100];
    sprintf(score_str, "Score: %d", score->score);
    SDL_FreeSurface(score->surface);
    SDL_DestroyTexture(score->texture);
    score->surface = TTF_RenderText_Solid(font, score_str, color);
    score->texture = SDL_CreateTextureFromSurface(renderer, score->surface);
    SDL_Rect rect = {SCORE_RECT.x, SCORE_RECT.y, score->surface->w/2, score->surface->h/2};
    SDL_RenderCopy(renderer, score->texture, NULL, &rect);
}
