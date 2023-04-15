#include "manage.h"

/**
 * 加载人物的不同动作的图像资源，对PlayerAction进行初始化
 * @param renderer 窗口的渲染器
 * @param Karyl_actions PlayerAction结构体数组
 */
void Load_Karyl_Actions(SDL_Renderer* renderer, PlayerAction* Karyl_actions[]) {
    int i;

    /* 初始化每种动作的图片和当前帧数 */
    for(i = 0;i < NUMS_OF_STATE; i++){
        Karyl_actions[i] = Create_Player_Action();
        Karyl_actions[i]->current_frame = 0;
    }

    /* 初始化每种动作的总帧数 */
    Karyl_actions[STATE_RUN]->nums_of_frames = FRAMES_RUN;
    Karyl_actions[STATE_JUMP]->nums_of_frames = FRAMES_JUMP;
    Karyl_actions[STATE_DIE]->nums_of_frames = FRAMES_DIE;

    /* 初始化每种动作的位置 */
    Karyl_actions[STATE_RUN]->rect = KARYL_RUN_RECT;
    Karyl_actions[STATE_JUMP]->rect = KARYL_JUMP_RECT;
    Karyl_actions[STATE_DIE]->rect = KARYL_DIE_RECT;

    /* 初始化每种动作的surface */
    Set_Player_Action_Surface(Karyl_actions[STATE_RUN], KARYL_RUN_PATH);
    Set_Player_Action_Surface(Karyl_actions[STATE_JUMP], KARYL_JUMP_PATH);
    Set_Player_Action_Surface(Karyl_actions[STATE_DIE], KARYL_DIE_PATH);

    /* 初始化每种动作的texture */
    Set_Player_Action_Texture(Karyl_actions[STATE_RUN], renderer);
    Set_Player_Action_Texture(Karyl_actions[STATE_JUMP], renderer);
    Set_Player_Action_Texture(Karyl_actions[STATE_DIE], renderer);
}

/**
 * 重置人物的动作数组
 * @param Karyl_actions PlayerAction结构体数组
 */
void Reset_Karyl_Actions(PlayerAction* Karyl_actions[]) {
    int i;

    /* 重置每种动作类型的当前帧数 */
    for(i = 0; i < NUMS_OF_STATE; i++) {
        Karyl_actions[i]->current_frame = 0;
    }

    /* 重置人物的位置 */
    Karyl_actions[STATE_RUN]->rect = KARYL_RUN_RECT;
    Karyl_actions[STATE_JUMP]->rect = KARYL_JUMP_RECT;
    Karyl_actions[STATE_DIE]->rect = KARYL_DIE_RECT;

}

/**
 * 释放PlayerAction数组
 * @param Karyl_actions PlayerAction结构体数组
 */
void Destroy_Karyl_Actions(PlayerAction* Karyl_actions[]) {
    int i;

    for(i = 0; i < NUMS_OF_STATE; i++) {
        Destroy_Player_Action(Karyl_actions[i]);
    }
}

/**
 * 加载不同怪物类型的图像资源，对MonsterModel数组进行初始化
 * @param renderer 窗口的渲染器
 * @param monster_actions MonsterModel结构体数组
 */
void Load_Monster_Model(SDL_Renderer* renderer, MonsterModel* monster_models[]) {
    int i, j, nums_of_type;
    char path[30];

    for(i = 0; i < NUMS_OF_MONSTER; i++) {
        monster_models[i] = (MonsterModel*)malloc(sizeof(MonsterModel));
        nums_of_type = i == MONSTER_GROUND ? GROUND_TYPE : AIR_TYPE;

        for(j = 0; j < nums_of_type; j++){
            sprintf(path, i==MONSTER_GROUND ? MONSTER_GROUND_PATH : MONSTER_AIR_PATH, j); /* 根据怪物类型和怪物编号格式化路径 */
            monster_models[i]->surface[j] = IMG_Load(path); /* 加载怪物的surface */
            monster_models[i]->texture[j] = SDL_CreateTextureFromSurface(renderer, monster_models[i]->surface[j]); /* 加载怪物的texture */
        }
    }

}

/**
 * 释放MonsterModel数组
 * @param monster_model MonsterModel结构体数组
 */
void Destroy_Monster_Models(MonsterModel* monster_model[]) {
    Destroy_Monster_Model(monster_model[MONSTER_GROUND], GROUND_TYPE);
    Destroy_Monster_Model(monster_model[MONSTER_AIR], AIR_TYPE);
}


