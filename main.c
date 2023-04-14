#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Rect_Queue.h"
#include <stringapiset.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "parameter.h"
#include "Player_Action.h"
#include "Monster_Model.h"
#include "load_resource.h"
#include "collision.h"
#include "score.h"
#include "record.h"


int DrawHomeScreen(SDL_Renderer* renderer); /* 游戏开始界面 */
int DrawMainScreen(SDL_Renderer* renderer, int *record); /* 游戏主界面 */
void DrawGameOverScreen(SDL_Renderer* renderer, int score); /* 游戏结束界面 */

PlayerAction* Karyl_actions[NUMS_OF_STATE];
MonsterModel* monster_models[NUMS_OF_MONSTER];

int main(int argc, char* argv[]) {
    int signal = SIGNAL_CONTINUE, game_score = 0;
    srand((unsigned)time(NULL));

    /* 初始化SDL */
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    /* 创建窗口和渲染器 */
    SDL_Window* window = SDL_CreateWindow("Parkour PCR", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Surface* icon = IMG_Load("parkour.ico");
    SDL_SetWindowIcon(window, icon);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Load_Karyl_Actions(renderer, Karyl_actions);
    Load_Monster_Model(renderer, monster_models);

    /* 游戏开始界面 */
    while(signal!=SIGNAL_QUIT){
        signal = DrawHomeScreen(renderer);
        if (signal == SIGNAL_QUIT) {
            break;
        }
        /* 主游戏界面 */
        signal = DrawMainScreen(renderer, &game_score);
    }

    Destroy_Karyl_Actions(Karyl_actions);
    Destroy_Monster_Models(monster_models);

    /* 释放资源 */
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_FreeSurface(icon);


    /* 退出 */
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();


    return 0;
}

int DrawHomeScreen(SDL_Renderer* renderer) {

    TTF_Font* font = TTF_OpenFont("font/font.ttf", 80); /* 加载字体 */
    SDL_Surface* home_screen = IMG_Load("images/bg_home.png"); /* 加载背景 */
    SDL_Surface* logo = IMG_Load("images/logo.png"); /* 加载logo */

    SDL_Color color = {255, 51, 153, 255};

    SDL_Surface* title = TTF_RenderUTF8_Blended(font, "公 主 连 结 跑 酷", color);

    //更改字体大小
    TTF_SetFontSize(font, 40);
    SDL_Surface* hint = TTF_RenderUTF8_Blended(font, "按ENTER开始游戏", (SDL_Color){255, 51, 153, 255});
    SDL_Texture* home_screen_texture = SDL_CreateTextureFromSurface(renderer, home_screen);
    SDL_Texture* logo_texture = SDL_CreateTextureFromSurface(renderer, logo);

    SDL_Rect home_screen_rect = {0, 0, 640, 480};
    SDL_Rect logo_rect = {190, 20, 250, 70};
    SDL_Rect title_rect = {85, 100, title->w, title->h};
    SDL_Rect hint_rect = {200, 250, hint->w, hint->h};

    SDL_RenderCopy(renderer, home_screen_texture, NULL, &home_screen_rect);
    SDL_RenderCopy(renderer, logo_texture, NULL, &logo_rect);
    SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, title), NULL, &title_rect);
    SDL_RenderCopy(renderer, SDL_CreateTextureFromSurface(renderer, hint), NULL, &hint_rect);


    SDL_RenderPresent(renderer);
    //按键检测
    SDL_Event event;
    int signal = SIGNAL_CONTINUE;
    while(signal==SIGNAL_CONTINUE) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                signal = SIGNAL_QUIT;
            }
            if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_RETURN) {
                    signal = SIGNAL_NEXT;
                }
            }
        }
    }

    SDL_DestroyTexture(home_screen_texture);
    SDL_DestroyTexture(logo_texture);


    SDL_FreeSurface(home_screen);
    SDL_FreeSurface(logo);
    SDL_FreeSurface(title);

    return signal;
}

int DrawMainScreen(SDL_Renderer* renderer, int* record){
    SDL_Surface* background = IMG_Load("images/bg.png");
    RectNode *node1 = NULL, *node2 = NULL;
    RectQueue* queue = InitRectQueue();

    SDL_Texture* background_texture = SDL_CreateTextureFromSurface(renderer, background);
    SDL_Texture* background_repeat_texture = SDL_CreateTextureFromSurface(renderer, background);

    CreateMonsterRectQueue(queue);
    node1 = DeRectQueue(queue);
    node2 = DeRectQueue(queue);

    SDL_Rect background_rect = {0, 0, 640, 480};
    SDL_Rect background_repeat_rect = {640, 0, 640, 480};
    SDL_Event event;
    //设置状态
    int state = STATE_RUN;
    int signal = SIGNAL_CONTINUE;
    int is_collision = 0;


    TTF_Font* font = TTF_OpenFont("font/font.ttf", 80);
    SDL_Color color = {255, 51, 153, 255};

    Score* score = InitScore();

    DrawScore(renderer, score, font, color);


    while(signal==SIGNAL_CONTINUE || signal==SIGNAL_WAIT) {

        /* 事件处理 */
        while(SDL_PollEvent(&event)) {

            /* 退出事件 */
            if(event.type == SDL_QUIT) {
                signal = SIGNAL_QUIT;
            }

            /* 键盘事件 */
            if (event.type == SDL_KEYDOWN) {
                /* 按下空格键，则改变角色状态 */
                if (event.key.keysym.sym == SDLK_SPACE && state == STATE_RUN) {
                    state = STATE_JUMP;
                }
            }
        }

        SDL_RenderCopy(renderer, background_texture, NULL, &background_rect);
        SDL_RenderCopy(renderer, background_repeat_texture, NULL, &background_repeat_rect);
        Draw_Monster_Model(renderer, monster_models, node1);
        Draw_Monster_Model(renderer, monster_models, node2);

        switch(state) {
            case STATE_RUN:
                Karyl_actions[STATE_RUN]->current_frame++;
                if(Karyl_actions[STATE_RUN]->current_frame >= FRAMES_RUN) {
                    Karyl_actions[STATE_RUN]->current_frame = 0;
                }

                Draw_Player_Action(renderer, Karyl_actions[STATE_RUN]);
                break;
            case STATE_JUMP:
                Karyl_actions[STATE_JUMP]->current_frame++;
                Karyl_actions[STATE_JUMP]->rect.y = 140 - JUMP_HEIGHT(Karyl_actions[STATE_JUMP]->current_frame);
                if(Karyl_actions[STATE_JUMP]->current_frame >= FRAMES_JUMP) {
                    Karyl_actions[STATE_JUMP]->current_frame = 0;
                    state = 0;
                }

                Draw_Player_Action(renderer, Karyl_actions[STATE_JUMP]);
                break;
            case STATE_DIE:
                Karyl_actions[STATE_DIE]->current_frame++;
                if(Karyl_actions[STATE_DIE]->current_frame >= FRAMES_DIE) {
                    Karyl_actions[STATE_DIE]->current_frame = 24;
                    signal = SIGNAL_NEXT;
                }
                Draw_Player_Action(renderer, Karyl_actions[STATE_DIE]);
                break;
            default:
                break;
        }
        //判断人物是否越过怪物
        if(state!=STATE_DIE && Karyl_actions[STATE_RUN]->rect.x >= node1->rect.x && node1->is_passed == 0) {
            node1->is_passed = 1;
            score->score++;
        }


        DrawScore(renderer, score, font, color);

        SDL_RenderPresent(renderer);

        is_collision = CollisionDetectPlayerMonster(Karyl_actions, state, monster_models, node1) ;
        if(is_collision == 1 && signal == SIGNAL_CONTINUE) {
            signal = SIGNAL_WAIT;
            state = STATE_DIE;
        }

        if(signal == SIGNAL_CONTINUE) {
            //背景滚动并将右边的部分用background_repeat填充
            background_rect.x -= 3;
            background_repeat_rect.x -= 3;
            node1->rect.x -= 8;
            node2->rect.x -= 8;
            if(background_rect.x <= -640) {
                background_rect.x = 640;
            }
            if(background_repeat_rect.x <= -640) {
                background_repeat_rect.x = 640;
            }

            if(node1->rect.x <= -100) {
                free(node1);
                FillMonsterRectQueue(queue);
                node1 = node2;
                node2 = DeRectQueue(queue);
                node2->rect.x += node1->rect.x;
            }
        }
        else if(signal == SIGNAL_NEXT) {
            DrawGameOverScreen(renderer, score->score);
        }

        SDL_Delay(1000/FPS);

    }

    free(node1);
    free(node2);
    DestroyRectQueue(queue);
    DestroyScore(score);
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(background_repeat_texture);
    SDL_FreeSurface(background);

    Reset_Karyl_Actions(Karyl_actions);


    return signal;
}

void DrawGameOverScreen(SDL_Renderer* renderer, int score){
    int quit = 0, record = read_record();
    record = score > record ? score : record;
    write_record(record);
    SDL_Surface* result = IMG_Load("images/text/result.png");
    SDL_Surface* board = IMG_Load("images/text/board.png");
    SDL_Texture* result_texture = SDL_CreateTextureFromSurface(renderer, result);
    SDL_Texture* board_texture = SDL_CreateTextureFromSurface(renderer, board);
    SDL_Rect result_rect = {225, 15, 200, 60};
    SDL_Rect board_rect = {120, 80, 400, 220};
    TTF_Font *font = TTF_OpenFont("font/font.ttf", 40);
    SDL_Color color = {255, 51, 153, 255};
    char score_str[25], record_str[25];
    sprintf(score_str, "Score:%15d", score);
    sprintf(record_str, "Record:%15d", record);
    SDL_Surface* score_surface = TTF_RenderText_Solid(font, score_str, color);
    SDL_Texture* score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);

    SDL_Surface* record_surface = TTF_RenderText_Solid(font, record_str, color);
    SDL_Texture* record_texture = SDL_CreateTextureFromSurface(renderer, record_surface);

    SDL_Surface* hint_surface = TTF_RenderText_Solid(font, "Press Enter to continue", color);
    SDL_Texture* hint_texture = SDL_CreateTextureFromSurface(renderer, hint_surface);

    SDL_Rect score_rect = {170, 100, 300, 40};
    SDL_Rect record_rect = {170, 160, 300, 40};
    SDL_Rect hint_rect = {170, 220, 300, 40};


    SDL_Event event;

    SDL_RenderCopy(renderer, board_texture, NULL, &board_rect);
    SDL_RenderCopy(renderer, result_texture, NULL, &result_rect);
    SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);
    SDL_RenderCopy(renderer, record_texture, NULL, &record_rect);
    SDL_RenderCopy(renderer, hint_texture, NULL, &hint_rect);

    SDL_RenderPresent(renderer);

    int signal = SIGNAL_CONTINUE;
    while(!quit){
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
            else if(event.type == SDL_KEYDOWN) {
                if(event.key.keysym.sym == SDLK_RETURN) {
                    quit = 1;
                }
            }
        }
    }

    SDL_DestroyTexture(result_texture);
    SDL_DestroyTexture(board_texture);
    SDL_DestroyTexture(score_texture);
    SDL_DestroyTexture(record_texture);
    SDL_DestroyTexture(hint_texture);

    SDL_FreeSurface(result);
    SDL_FreeSurface(board);
    SDL_FreeSurface(score_surface);
    SDL_FreeSurface(record_surface);
    SDL_FreeSurface(hint_surface);


}





