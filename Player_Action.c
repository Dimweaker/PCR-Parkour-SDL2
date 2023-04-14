#include "Player_Action.h"

PlayerAction* Create_Player_Action(){
    PlayerAction* action = (PlayerAction*)malloc(sizeof(PlayerAction));
    return action;
}

void Set_Player_Action_Surface(PlayerAction* action, char* path_format){
    int i;
    for(i = 0; i < (action->nums_of_frames); i++) {
        char path[100];
        sprintf(path, path_format, i+1);
        action->surface[i] = IMG_Load(path);
    }
}

void Set_Player_Action_Texture(PlayerAction* action, SDL_Renderer* renderer){
    int i;
    for(i = 0; i < action->nums_of_frames; i++) {
        action->texture[i] = SDL_CreateTextureFromSurface(renderer, action->surface[i]);
    }
}

void Destroy_Player_Action(PlayerAction* action){
    int i;
    for(i = 0; i < action->nums_of_frames; i++) {
        SDL_FreeSurface(action->surface[i]);
        SDL_DestroyTexture(action->texture[i]);
    }
    free(action);

}

void Draw_Player_Action(SDL_Renderer* renderer, PlayerAction* action){
    int frame = action->current_frame;

    SDL_RenderCopy(renderer, action->texture[frame], NULL, &action->rect);
}
