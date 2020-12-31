//
//  main.c
//  leftedge_router
//
//  Created by 陳民嶧 on 2020/12/2.
//  Copyright © 2020 陳民嶧. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include "graph.h"
#define max_line 100






int main(int argc, const char * argv[]) {
    
    int length=0;//channel 長度
    int N=0;//net的數量
    char c[max_line]={0};
    //read input file
    FILE *f1;
    f1 = fopen("/Users/tatopus/Document/Git/GreedyRouter/444858_n4.dat", "r");
    assert(f1 != NULL);
    fgets(c,max_line,f1);
    sscanf(c,"NumNet %d",&N);
    fgets(c,max_line,f1);
    sscanf(c,"ChannelLength %d",&length);
    int flag =0;
    char * pch;
    int col;
    char position;
    int top[length];
    int bottom[length];
    for(int i=0; i<length; i++){
        top[i] =-1;
        bottom[i] = -1;
    }
    int net_num=0;
    int net_count[N];
    for(int i =0; i<N; i++) {
        net_count[i] = 0;
    }
    while(fgets(c,max_line,f1) != NULL){
        pch = strtok(c," ");
        while (pch != NULL)
        {
            
            if(flag > 1) {
                sscanf(pch,"%1s%d",&position, &col);
                switch (position) {
                    case 't':
                        top[col] = net_num;
                        net_count[net_num] ++;
                        break;
                    case 'b':
                        bottom[col] = net_num;
                        net_count[net_num] ++;
                        break;
                    default:
                        break;
                }
            }
            flag ++;
            pch = strtok(NULL, " ");
        }
        net_num ++;
    }
    fclose(f1);
    printf("top   :");
    for(int i =0; i<length; i++){
        printf("%2d ", top[i]);
    }
    printf("\nbottom:");
    for(int i =0; i<length; i++) {
        printf("%2d ", bottom[i]);
    }
    printf("\n");
    
    
    //interval[net][left or right];
    int interval[N][2]; //interval[1][1]: net 1的最左端在的位置，interval[1][2]：net 1 最右端的位置
    for (int i = 0; i<N; i++){
        for(int j =0; j<2; j++) {
            interval[i][j] = -1;
        }
    }
    for(int i = 0; i< length; i++) {
        if(interval[top[i]][0] == -1) {
            interval[top[i]][0] = i;
        }
        if(interval[bottom[i]][0] == -1) {
            interval[bottom[i]][0] = i;
        }
        if(i >= interval[top[i]][1]) {
            interval[top[i]][1] = i;
        }
        if(i >= interval[bottom[i]][1]) {
            interval[bottom[i]][1] = i;
        }
    }
    
    for(int i = 0; i<N; i++) {
        printf("Net %d interval : %d, %d\n", i, interval[i][0], interval[i][1]);
    }
        
        
        
        
       // input array containing edges of the graph (as per above diagram)
       // (x, y) pair in the array represents an edge from x to y
    /*printf("start");
    int mm = 1;
    pp(mm);
    printf("2\n");
    struct Edge edges[] =
    {
        { 0, 1 }, { 1, 2 }, { 2, 0 }, { 2, 1 },
        { 3, 2 }, { 4, 5 }, {5,4}
    };
    
       // calculate number of edges
    int n = sizeof(edges)/sizeof(edges[0]);

    // construct graph from given edges
    struct Graph *graph = createGraph(edges, n);
    
    // print adjacency list representation of graph
    printGraph(graph);
    deletNode(graph, 5, 4);
    if(isempty(graph, 5)){
        printf("list of 5 is empty\n");
    }
    else
        printf("list of 5 is not empty\n");
    printGraph(graph);
    free(graph);
     */
    return 0;
}

