#include "SDL2/SDL.h"
#include "parameter.h"

#ifndef PARKOUR_RECT_QUEUE_H
#define PARKOUR_RECT_QUEUE_H
/* 怪物的节点，用于存储怪物的信息 */
typedef struct RectNode {
    SDL_Rect rect; /* 怪物的位置 */
    int rect_index; /* 怪物的索引 */
    int rect_type; /* 怪物的种类，分空中和地面 */
    int monster; /* 怪物的类型，在空中或地面的基础上细分 */
    int is_passed; /* 是否已经被通过 */
    struct RectNode* next; /* 指向下一个节点 */
} RectNode;

/* 怪物的队列，用于存储怪物的节点，以链式列表进行存储 */
typedef struct RectQueue {
    RectNode* front;
    RectNode* rear;
    int size;
} RectQueue;

RectQueue* InitRectQueue();
void EnRectQueue(RectQueue* queue, SDL_Rect rect, int rect_type, int monster);
RectNode* DeRectQueue(RectQueue* queue);
void DestroyRectQueue(RectQueue* queue);
void CreateMonsterRectQueue(RectQueue* queue);
void FillMonsterRectQueue(RectQueue* queue);
int random_monster(int monster_type);
#endif
