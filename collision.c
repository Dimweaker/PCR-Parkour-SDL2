#include "collision.h"

/**
 * 获取指定(x,y)坐标的像素值
 * @param surface 获取像素值的目标surface
 * @param x 像素的x坐标
 * @param y 像素的y坐标
 * @return 指定位置的像素值（Uint32）
 */
Uint32 get_pixel(SDL_Surface* surface, int x, int y) {

    int bpp = surface->format->BytesPerPixel; /* 每个像素的字节数 */
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp; /* 指向目标像素的指针 */

    /* 根据不同的像素格式，进行不同的位运算 */
    switch (bpp) {
        case 1:
            return *p;
        case 2:
            return *(Uint16*)p;
        case 3:
            return p[0] | p[1] << 8 | p[2] << 16;
        case 4:
            return *(Uint32*)p;
        default:
            return 0;
    }
}

/**
 * 两个矩形的碰撞检测
 * @param rect1 矩形1的位置
 * @param surface1 矩形1的surface
 * @param rect2 矩形2的位置
 * @param surface2 矩形2的surface
 * @return 是否相撞，1为相撞，0为不相撞
 */
int CollisionDetect(SDL_Rect rect1, SDL_Surface* surface1, SDL_Rect rect2, SDL_Surface* surface2){

    SDL_Rect intersect_rect; /* 两个矩形的交集矩形 */
    Uint8 alpha1, alpha2, red1, red2, green1, green2, blue1, blue2; /* 两个矩形的像素的RGBA值 */

    /* 如果两个矩形相交 */
    if(SDL_IntersectRect(&rect1, &rect2, &intersect_rect)==SDL_TRUE) {
        int  x, y;

        for(y = intersect_rect.y; y < intersect_rect.y + intersect_rect.h; y++) {
            for(x = intersect_rect.x; x < intersect_rect.x + intersect_rect.w; x++) {
                /* 获取两个矩形的交集矩形中的每个像素 */
                Uint32 pixel1 = get_pixel(surface1, x - rect1.x, y - rect1.y);
                Uint32 pixel2 = get_pixel(surface2, x - rect2.x, y - rect2.y);

                /* 获取像素的RGBA值 */
                SDL_GetRGBA(pixel1, surface1->format, &red1, &green1, &blue1, &alpha1);
                SDL_GetRGBA(pixel2, surface2->format, &red2, &green2, &blue2, &alpha2);

                /* 如果两个像素的alpha值都不为0，则两个矩形相交 */
                if(alpha1 != 0 && alpha2 != 0) {
                    return 1;
                }
            }
        }
    }
    /* 如果两个矩形不相交 */
    else{
        return 0;
    }
}

/**
 * 玩家与怪物的碰撞检测
 * @param action 玩家的动作
 * @param state 玩家的状态
 * @param model 怪物的模型
 * @param node 怪物的位置
 * @return 是否相撞，1为相撞，0为不相撞
 */
int CollisionDetectPlayerMonster(PlayerAction* action[], int state, MonsterModel* model[], RectNode* node){
    int monster_type = node->rect_type, monster = node->monster;
    SDL_Rect rect = node->rect;
    SDL_Surface* surface = model[monster_type]->surface[monster];
    SDL_Rect player_rect = action[state]->rect;
    SDL_Surface* player_surface = action[state]->surface[action[state]->current_frame];
    return CollisionDetect(player_rect, player_surface, rect, surface);
}