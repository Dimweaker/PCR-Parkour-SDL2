#include <stdio.h>
#include <stdlib.h>
#include "Rect_Queue.h"

RectQueue* InitRectQueue() {
    RectQueue* queue = (RectQueue*)malloc(sizeof(RectQueue));
    queue->front = queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void EnRectQueue(RectQueue* queue, SDL_Rect rect, int rect_type) {
    RectNode* node = (RectNode*)malloc(sizeof(RectNode));
    node->rect = rect;
    node->rect_type = rect_type;
    node->is_passed = 0;
    node->next = NULL;
    if(queue->rear == NULL) {
        node->rect_index = 0;
        queue->front = queue->rear = node;
    } else {
        node->rect_index = queue->rear->rect_index + 1;
        queue->rear->next = node;
        queue->rear = node;
    }
    queue->size++;
}

RectNode* DeRectQueue(RectQueue* queue) {
    if(queue->front == NULL) {
        printf("Error: DeRectQueue() failed, queue is empty");
        exit(1);
    }
    RectNode* node = queue->front;
    SDL_Rect rect = node->rect;
    queue->front = node->next;
    if(queue->front == NULL) {
        queue->rear = NULL;
    }
    queue->size--;
    return node;
}

void DestroyRectQueue(RectQueue* queue) {
    while(queue->front != NULL) {
        RectNode* node = queue->front;
        queue->front = node->next;
        free(node);
    }
    free(queue);
}

void CreateMonsterRectQueue(RectQueue* queue){
    int i, rect_type;
    for(i = 0; i < NUMS_OF_MONSTER; i++) {
        rect_type = rand() % 2;
        switch (rect_type) {
            case MONSTER_GROUND:
                EnRectQueue(queue,
                            (SDL_Rect) {500 + i * 400, MONSTER_GROUND_Y, MONSTER_GROUND_WIDTH, MONSTER_GROUND_HEIGHT},
                            rect_type);
                break;
            case MONSTER_AIR:
                EnRectQueue(queue,
                            (SDL_Rect) {500 + i * 400, MONSTER_AIR_Y, MONSTER_AIR_WIDTH, MONSTER_AIR_HEIGHT},
                            rect_type);
                break;
            default:
                printf("error type");
        }

    }
}

void FillMonsterRectQueue(RectQueue* queue){
    int rect_type, rand_distance_x, rand_distance_y;
    rect_type = rand() % 10 < 8 ? MONSTER_GROUND : MONSTER_AIR;
    rand_distance_x = rand() % 150 - 40;
    rand_distance_y = rand() % 30 - 15;
    switch (rect_type) {
        case MONSTER_GROUND:
            EnRectQueue(queue,
                        (SDL_Rect) {500 + rand_distance_x, MONSTER_GROUND_Y + rand_distance_y, MONSTER_GROUND_WIDTH, MONSTER_GROUND_HEIGHT},
                        rect_type);
            break;
        case MONSTER_AIR:
            EnRectQueue(queue,
                        (SDL_Rect) {500 + rand_distance_x, MONSTER_AIR_Y + rand_distance_y, MONSTER_AIR_WIDTH, MONSTER_AIR_HEIGHT},
                        rect_type);
            break;

        default:
            printf("error type");
    }
}



