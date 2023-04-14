#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "Player_Action.h"
#include "Monster_Model.h"
#include "parameter.h"

#ifndef PARKOUR_LOAD_RESOURCE_H
#define PARKOUR_LOAD_RESOURCE_H

void Load_Karyl_Actions(SDL_Renderer* renderer, PlayerAction* Karyl_actions[]);
void Load_Monster_Model(SDL_Renderer* renderer, MonsterModel* monster_models[]);

void Reset_Karyl_Actions(PlayerAction* Karyl_actions[]);

void Destroy_Karyl_Actions(PlayerAction* Karyl_actions[]);
void Destroy_Monster_Models(MonsterModel* monster_model[]);

#endif //PARKOUR_LOAD_RESOURCE_H
