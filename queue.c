//
//  queue.c
//  leftedge_router
//
//  Created by 陳民嶧 on 2021/1/7.
//  Copyright © 2021 陳民嶧. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"

void init_queue(Queue *q) {
    q->front = NULL;
    q -> rear = NULL;
}

int empty(Queue *q) {
    return (q->front == NULL && q->rear == NULL);
}
void enqueue(Queue *q, int data) {
    
    Listnode *current = (Listnode *)malloc(sizeof(Listnode));
    assert(current != NULL);
    current -> data = data;
    if(q->front == NULL) {
        q -> front = current;
        q -> rear = current;
        return;
    }
    q -> rear -> next = current;
    q -> rear = current;
    
}
int dequeue(Queue *q) {
    if(empty(q)) {
        printf("The queue is empty");
        return -1;
    }
    int i = q -> front -> data;
    if(q -> front == q -> rear) {
        free(q -> front);
        q -> front = NULL;
        q -> rear = NULL;
    }
    else {
        Listnode *current = q -> front;
        q -> front = current -> next;
        free(current);
    }
    return i;
}
