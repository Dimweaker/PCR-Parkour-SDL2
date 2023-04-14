#include "Monster_Model.h"
#include "Rect_Queue.h"
#include "Player_Action.h"
#ifndef PARKOUR_COLLISION_H
#define PARKOUR_COLLISION_H
Uint32 get_pixel(SDL_Surface* surface, int x, int y);
int CollisionDetect(SDL_Rect rect1, SDL_Surface* surface1, SDL_Rect rect2, SDL_Surface* surface2);
int CollisionDetectPlayerMonster(PlayerAction* action[], int state, MonsterModel* model[], RectNode* node);
#endif //PARKOUR_COLLISION_H
