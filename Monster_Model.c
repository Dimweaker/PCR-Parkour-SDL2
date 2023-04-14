#include "Monster_Model.h"

void Destroy_Monster_Model(MonsterModel* model){
    SDL_DestroyTexture(model->texture);
    SDL_FreeSurface(model->surface);
    free(model);
}

void Draw_Monster_Model(SDL_Renderer* renderer, MonsterModel* model[], RectNode* node){
    int monster_type = node->rect_type;

    SDL_Rect rect = node->rect;
    SDL_RenderCopy(renderer, model[monster_type]->texture, NULL, &rect);
}

