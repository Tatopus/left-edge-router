//
//  queue.h
//  leftedge_router
//
//  Created by 陳民嶧 on 2021/1/7.
//  Copyright © 2021 陳民嶧. All rights reserved.
//

#ifndef queue_h
#define queue_h

#include <stdio.h>

#endif /* queue_h */

struct listnode {
    int data;
    struct listnode *next;
};
typedef struct listnode Listnode;

struct queue {
    Listnode *front;
    Listnode *rear;
};
typedef struct queue Queue;

void init_queue(Queue *q);
int empty(Queue *q);
void enqueue(Queue *q, int data);
int dequeue(Queue *q);
