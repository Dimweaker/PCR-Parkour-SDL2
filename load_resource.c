#include "load_resource.h"

void Load_Karyl_Actions(SDL_Renderer* renderer, PlayerAction* Karyl_actions[]) {
    int i;

    for(i = 0;i < NUMS_OF_STATE; i++){
        Karyl_actions[i] = Create_Player_Action();
        Karyl_actions[i]->current_frame = 0;
    }

    Karyl_actions[STATE_RUN]->nums_of_frames = FRAMES_RUN;
    Karyl_actions[STATE_JUMP]->nums_of_frames = FRAMES_JUMP;
    Karyl_actions[STATE_DIE]->nums_of_frames = FRAMES_DIE;

    Karyl_actions[STATE_RUN]->rect = KARYL_RUN_RECT;
    Karyl_actions[STATE_JUMP]->rect = KARYL_JUMP_RECT;
    Karyl_actions[STATE_DIE]->rect = KARYL_DIE_RECT;

    Set_Player_Action_Surface(Karyl_actions[STATE_RUN], KARYL_RUN_PATH);
    Set_Player_Action_Surface(Karyl_actions[STATE_JUMP], KARYL_JUMP_PATH);
    Set_Player_Action_Surface(Karyl_actions[STATE_DIE], KARYL_DIE_PATH);

    Set_Player_Action_Texture(Karyl_actions[STATE_RUN], renderer);
    Set_Player_Action_Texture(Karyl_actions[STATE_JUMP], renderer);
    Set_Player_Action_Texture(Karyl_actions[STATE_DIE], renderer);
}

void Reset_Karyl_Actions(PlayerAction* Karyl_actions[]) {
    int i;

    for(i = 0; i < NUMS_OF_STATE; i++) {
        Karyl_actions[i]->current_frame = 0;
    }

    Karyl_actions[STATE_RUN]->rect = KARYL_RUN_RECT;
    Karyl_actions[STATE_JUMP]->rect = KARYL_JUMP_RECT;
    Karyl_actions[STATE_DIE]->rect = KARYL_DIE_RECT;

}
void Destroy_Karyl_Actions(PlayerAction* Karyl_actions[]) {
    int i;

    for(i = 0; i < NUMS_OF_STATE; i++) {
        Destroy_Player_Action(Karyl_actions[i]);
    }
}

void Load_Monster_Model(SDL_Renderer* renderer, MonsterModel* monster_models[]) {
    int i;

    for(i = 0; i < NUMS_OF_MONSTER; i++) {
        monster_models[i] = (MonsterModel*)malloc(sizeof(MonsterModel));
    }

    monster_models[MONSTER_GROUND]->surface = IMG_Load(MONSTER_GROUND_PATH);
    monster_models[MONSTER_AIR]->surface = IMG_Load(MONSTER_AIR_PATH);

    monster_models[MONSTER_GROUND]->texture = SDL_CreateTextureFromSurface(renderer, monster_models[MONSTER_GROUND]->surface);
    monster_models[MONSTER_AIR]->texture = SDL_CreateTextureFromSurface(renderer, monster_models[MONSTER_AIR]->surface);

}

void Destroy_Monster_Models(MonsterModel* monster_model[]) {
    int i;

    for(i = 0; i < NUMS_OF_MONSTER; i++) {
        Destroy_Monster_Model(monster_model[i]);
    }
}


