//
//  graph.c
//  leftedge_router
//
//  Created by 陳民嶧 on 2020/12/22.
//  Copyright © 2020 陳民嶧. All rights reserved.
//
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void printGraph(struct Graph* graph)
{
    
    int i;
    for (i = 0; i < NN; i++)
    {
        
        // print current vertex and all its neighbors
        struct Node* ptr = graph->head[i];
        if(ptr != NULL) {
            while (ptr != NULL)
            {
                
                printf("(%d -> %d)\t", i, ptr->dest);
                ptr = ptr->next;
            }
            printf("\n");
        }
    }
    printf("\n");
}

int isempty(struct Graph* graph, int index) {
    struct Node* ptr = graph->head[index];
    int flag = 1;
    while(ptr != NULL) {
        if(ptr -> dest != -1)
            flag = 0 ;
        ptr = ptr -> next;
    }
    
    return flag;
}

void deletNode(struct Graph* graph, int src, int dest){
    struct Node* ptr = graph -> head[src];
    if(isempty(graph, src)){
        
    }
    else{
        while(ptr != NULL) {
            
            if(ptr ->dest == dest){
                ptr -> dest = -1;
                break;
            }
            ptr = ptr -> next;
        }
    }
}

struct Graph* createGraph(struct Edge edges[], int n)
{
    unsigned i;
 
    // allocate memory for graph data structure
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
 
    // initialize head pointer for all vertices
    for (i = 0; i < NN; i++)
        graph->head[i] = NULL;
 
    // add edges to the directed graph one by one
    for (i = 0; i < n; i++)
    {
        // get source and destination vertex
        int src = edges[i].src;
        int dest = edges[i].dest;
 
        // allocate new node of Adjacency List from src to dest
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->dest = dest;
 
        // point new node to current head
        newNode->next = graph->head[src];
 
        // point head pointer to new node
        graph->head[src] = newNode;
    }
 
    return graph;
}

void pp(int i) {
    printf("%d",i);
}
