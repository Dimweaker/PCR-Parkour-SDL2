#include "Monster_Model.h"

/**
 * 释放怪物模型的内存
 * @param model 怪物模型的指针
 * @param n 该模型怪物的类型数量
 */
void Destroy_Monster_Model(MonsterModel* model, int n){
    int i;
    for(i = 0; i < n; i++){
        SDL_DestroyTexture(model->texture[i]);
        SDL_FreeSurface(model->surface[i]);
    }
    free(model);
}

/**
 * 绘制怪物
 * @param renderer 窗口的渲染器
 * @param model 怪物模型的数组
 * @param node 怪物的位置信息
 */
void Draw_Monster_Model(SDL_Renderer* renderer, MonsterModel* model[], RectNode* node){
    int monster_type = node->rect_type, monster = node->monster;
    SDL_Rect rect = node->rect;
    SDL_RenderCopy(renderer, model[monster_type]->texture[monster], NULL, &rect);
}

