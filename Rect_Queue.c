#include <stdio.h>
#include <stdlib.h>
#include "Rect_Queue.h"

/**
 * 初始化队列
 * @return 返回一个队列的指针
 */
RectQueue* InitRectQueue() {
    RectQueue* queue = (RectQueue*)malloc(sizeof(RectQueue));
    queue->front = queue->rear = NULL;
    queue->size = 0;
    return queue;
}

/**
 * 入队
 * @param queue 队列的指针
 * @param rect 怪物的位置
 * @param rect_type 怪物的种类
 * @param monster 怪物的类型
 */
void EnRectQueue(RectQueue* queue, SDL_Rect rect, int rect_type, int monster) {
    RectNode* node = (RectNode*)malloc(sizeof(RectNode));
    node->rect = rect;
    node->rect_type = rect_type;
    node->is_passed = 0;
    node->next = NULL;
    node->monster = monster;

    if(queue->rear == NULL) {
        node->rect_index = 0;
        queue->front = queue->rear = node;
    }
    else {
        node->rect_index = queue->rear->rect_index + 1;
        queue->rear->next = node;
        queue->rear = node;
    }
    queue->size++;
}

/**
 * 出队
 * @param queue 队列的指针
 * @return 返回一个怪物节点的指针
 */
RectNode* DeRectQueue(RectQueue* queue) {
    if(queue->front == NULL) {
        printf("Error: DeRectQueue() failed, queue is empty");
        exit(1);
    }
    RectNode* node = queue->front;
    queue->front = node->next;
    if(queue->front == NULL) {
        queue->rear = NULL;
    }
    queue->size--;
    return node;
}

/**
 * 销毁队列
 * @param queue 队列的指针
 */
void DestroyRectQueue(RectQueue* queue) {
    while(queue->front != NULL) {
        RectNode* node = queue->front;
        queue->front = node->next;
        free(node);
    }
    free(queue);
}

/**
 * 创建怪物队列，生成初始怪物的节点
 * @param queue
 */
void CreateMonsterRectQueue(RectQueue* queue){
    int i, rect_type, monster;
    for(i = 0; i < NUMS_OF_MONSTER; i++) {
        rect_type = rand() % 2; /* 随机生成怪物的种类 */
        monster = random_monster(rect_type); /* 随机生成怪物的类型 */

        /* 根据怪物的种类和类型，生成怪物的位置 */
        switch (rect_type) {
            case MONSTER_GROUND:
                EnRectQueue(queue,
                            (SDL_Rect) {500 + i * 400, MONSTER_GROUND_Y, MONSTER_GROUND_WIDTH, MONSTER_GROUND_HEIGHT},
                            rect_type, monster);
                break;
            case MONSTER_AIR:
                EnRectQueue(queue,
                            (SDL_Rect) {500 + i * 400, MONSTER_AIR_Y, MONSTER_AIR_WIDTH, MONSTER_AIR_HEIGHT},
                            rect_type, monster);
                break;
            default:
                printf("error type");
        }

    }
}

/**
 * 填充怪物队列，生成新的怪物节点
 * @param queue
 */
void FillMonsterRectQueue(RectQueue* queue){
    int rect_type, rand_distance_x, rand_distance_y, monster;
    rect_type = rand() % 10 < 8 ? MONSTER_GROUND : MONSTER_AIR; /* 随机生成怪物的种类，以0.8的概率生成地面怪物，0.2的概率生成空中怪物 */
    rand_distance_x = rand() % 150 - 40; /* 随机生成怪物的x坐标偏移量 */
    rand_distance_y = rand() % 30 - 15; /* 随机生成怪物的y坐标偏移量 */
    monster = random_monster(rect_type); /* 随机生成怪物的类型 */

    /* 根据怪物的种类和类型，生成怪物的位置 */
    switch (rect_type) {
        case MONSTER_GROUND:
            EnRectQueue(queue,
                        (SDL_Rect) {500 + rand_distance_x, MONSTER_GROUND_Y + rand_distance_y, MONSTER_GROUND_WIDTH, MONSTER_GROUND_HEIGHT},
                        rect_type, monster);
            break;
        case MONSTER_AIR:
            EnRectQueue(queue,
                        (SDL_Rect) {500 + rand_distance_x, MONSTER_AIR_Y + rand_distance_y, MONSTER_AIR_WIDTH, MONSTER_AIR_HEIGHT},
                        rect_type, monster);
            break;

        default:
            printf("error type");
    }
}

/**
 * 随机生成怪物的类型
 * @param monster_type 怪物的种类
 * @return 返回怪物的类型
 */
int random_monster(int monster_type){
    int monster, n;
    n = monster_type == MONSTER_GROUND ? GROUND_TYPE : AIR_TYPE;
    monster = rand() % n;
    return monster;
}


