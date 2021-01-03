//
//  graph.h
//  leftedge_router
//
//  Created by 陳民嶧 on 2020/12/22.
//  Copyright © 2020 陳民嶧. All rights reserved.
//



// A data structure to store graph edges
// Define maximum number of vertices in the graph
#define NN 40
 
// Data structure to store graph
struct Graph {
    // An array of pointers to Node to represent adjacency list
    struct Node* head[NN];
    int assigned[NN];
};
 
// A data structure to store adjacency list nodes of the graph
struct Node {
    int dest;
    struct Node* next;
};
 
// data structure to store graph edges
struct Edge {
    int src, dest;
};
 
// Function to create an adjacency list from specified edges
struct Graph* createGraph(struct Edge edges[], int n);
void printGraph(struct Graph* graph);
int isempty(struct Graph* graph, int index);
void deletNode(struct Graph* graph, int src, int dest);
void pp(int i);
