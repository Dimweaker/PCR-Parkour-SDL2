#include "collision.h"

Uint32 get_pixel(SDL_Surface* surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
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

int CollisionDetect(SDL_Rect rect1, SDL_Surface* surface1, SDL_Rect rect2, SDL_Surface* surface2){
    SDL_Rect intersect_rect;

    if(SDL_IntersectRect(&rect1, &rect2, &intersect_rect)==SDL_TRUE) {
        int  x, y;
        for(y = intersect_rect.y; y < intersect_rect.y + intersect_rect.h; y++) {
            for(x = intersect_rect.x; x < intersect_rect.x + intersect_rect.w; x++) {
                Uint32 pixel1 = get_pixel(surface1, x - rect1.x, y - rect1.y);
                Uint32 pixel2 = get_pixel(surface2, x - rect2.x, y - rect2.y);
                Uint8 alpha1, alpha2, red1, red2, green1, green2, blue1, blue2;
                SDL_GetRGBA(pixel1, surface1->format, &red1, &green1, &blue1, &alpha1);
                SDL_GetRGBA(pixel2, surface2->format, &red2, &green2, &blue2, &alpha2);
                if(alpha1 != 0 && alpha2 != 0) {
                    return 1;
                }
            }
        }
    }
    else{
        return 0;
    }
}

int CollisionDetectPlayerMonster(PlayerAction* action[], int state, MonsterModel* model[], RectNode* node){
    int monster_type = node->rect_type;
    SDL_Rect rect = node->rect;
    SDL_Surface* surface = model[monster_type]->surface;
    SDL_Rect player_rect = action[state]->rect;
    SDL_Surface* player_surface = action[state]->surface[action[state]->current_frame];
    return CollisionDetect(player_rect, player_surface, rect, surface);
}