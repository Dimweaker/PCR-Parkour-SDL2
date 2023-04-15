#include "Player_Action.h"

/**
 * 创建一个PlayerAction结构体
 * @return 一个PlayerAction结构体
 */
PlayerAction* Create_Player_Action(){
    PlayerAction* action = (PlayerAction*)malloc(sizeof(PlayerAction));
    return action;
}

/**
 * 设置PlayerAction的surface
 * @param action PlayerAction结构体指针
 * @param path_format 路径格式
 */
void Set_Player_Action_Surface(PlayerAction* action, char* path_format){
    int i;
    for(i = 0; i < (action->nums_of_frames); i++) {
        char path[100];
        sprintf(path, path_format, i+1); /* 格式化路径 */
        action->surface[i] = IMG_Load(path); /* 加载图片 */
    }
}

/**
 * 设置PlayerAction的texture
 * @param action PlayerAction结构体指针
 * @param renderer 窗口的渲染器
 */
void Set_Player_Action_Texture(PlayerAction* action, SDL_Renderer* renderer){
    int i;
    for(i = 0; i < action->nums_of_frames; i++) {
        action->texture[i] = SDL_CreateTextureFromSurface(renderer, action->surface[i]);
    }
}

/**
 * 销毁PlayerAction结构体
 * @param action PlayerAction结构体指针
 */
void Destroy_Player_Action(PlayerAction* action){
    int i;
    for(i = 0; i < action->nums_of_frames; i++) {
        SDL_FreeSurface(action->surface[i]);
        SDL_DestroyTexture(action->texture[i]);
    }
    free(action);

}

/**
 * 绘制PlayerAction
 * @param renderer 窗口的渲染器
 * @param action PlayerAction结构体指针
 */
void Draw_Player_Action(SDL_Renderer* renderer, PlayerAction* action){
    int frame = action->current_frame;

    SDL_RenderCopy(renderer, action->texture[frame], NULL, &action->rect);
}
