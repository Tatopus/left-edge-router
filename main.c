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
    f1 = fopen("/Users/tatopus/Document/Git/GreedyRouter/444858_n30.dat", "r");
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
    
    
    //interval[net][left or right];
    int interval[N][2]; //interval[1][1]: net 1的最左端在的位置，interval[1][2]：net 1 最右端的位置

    for (int i = 0; i<N; i++){
        for(int j =0; j<2; j++) {
            interval[i][j] = -1;
        }
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
    
    
    //把所有net加入interval中
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
    
    
    //印出所有interval
    for(int i = 0; i<N; i++) {
        printf("Net %d interval : %d, %d\n", i, interval[i][0], interval[i][1]);
    }
    printf("\n");
    
    //把所有配對加入edge給之後建立graph使用
    struct Edge edges[length];
    for(int i = 0; i<length; i++) {
        edges[i].dest = top[i];
        edges[i].src = bottom[i];
    }
    
    
    //construct a graph from the edges
    struct Graph *vcg = createGraph(edges, length);
    printGraph(vcg);
    int track_flag[N];
    int track[N][length];
    for(int i = 0; i<N; i++){
        track_flag[i] = -1;
        vcg->assigned[i] = 0;
        for(int j =0; j<length; j++) {
            track[i][j] =-1;
        }
    }
    int clear_flag = 1;//用來確認即將放入的軌道是否為空的 1是空的, -1就不為空
    int assigned_count = 0;
    int assigned_flag = 0;
    
    //routing
    while(assigned_count < N) {
        for(int i = 0; i< N; i++) {
            if(vcg->assigned[i] ==0){
                assigned_flag = 0;
                clear_flag = 1;
                int current_net = i;
                if(isempty(vcg, current_net)){ // 如果ｖｃｇ是空的（沒有vertical constrain，就可以開始進行assign
                    for(int j =0; j<N; j++) {//從track[N][length] 搜尋可以用的track
                        if(track_flag[j] == -1 ){ //如果目前 track 是空的，直接把 net 放進去
                            track_flag[j] = 1; //表示track目前已被佔用;
                            assigned_flag = 1;
                            for(int k = interval[current_net][0] ; k <= interval[current_net][1]; k++){ // 把track填上ｎｅｔ的數字
                                track[j][k] = i;
                            }
                            //放進去後把node從graph中刪除
                            for(int z = 0; z< N; z++){
                                deletNode(vcg, z, current_net);
                            }
                            printGraph(vcg);
                        }
                        else{//如果net不是空的，檢查新的net有沒有辦法放進去目前的track中
                            int temp_left = interval[current_net][0];
                            int temp_right = interval[current_net][1];
                            if(track[j][temp_left] == -1 && track[j][temp_right] == -1) { //檢查要放進去的位置是不是空的
                                for(int k = temp_left; k< temp_right; k++){
                                    if(track[j][k] != -1) { // 如果即將要放入的軌道中有其中一格有被佔用，flag就為-1
                                        clear_flag = 0;
                                    }
                                    
                                }
                                if(clear_flag ){ //clear flag = 1; 代表是空的; //把net assigned近來
                                    assigned_flag = 1;
                                    for(int m= temp_left; m <= temp_right; m++){
                                        track[j][m] = i;
                                    }
                                    for(int z = 0; z< N; z++){//放進去後把node從graph中刪除
                                        deletNode(vcg, z, current_net);
                                    }
                                    printGraph(vcg);
                                }
                            }
                        }
                        if(assigned_flag == 1) {
                            assigned_count ++; //表示這條net將會被assign
                            vcg->assigned[i] = 1;
                            break; // 跳出找空track的迴圈
                        }
                    }// end of for(j = 0) Loop of finding empty track
                }// end of isempty(vcg, current), assign net has no VC to a track
            }
            if(assigned_count == N)
                break;
        }// end of for(int i) finding a net with no vertical constrain
    }// end of while
    
    
    printf("Routing result: \n");
    printf("top      : ");
    for(int i =0; i<length; i++){
        printf("%3d ", top[i]);
    }
    printf("\n");
    printf("\n");
    
    for(int i = 0; i < N ; i++) {
        if(track_flag[i] != -1){
            printf("track %2d : ", i+1);
            for(int j = 0; j< length; j++){
                printf(" %2d ", track[i][j]);
            }
            printf("\n");
        }
    }
    printf("\n");
    
    printf("bottom   : ");
    for(int i =0; i<length; i++) {
        printf("%3d ", bottom[i]);
    }
    printf("\n");

    
    free(vcg);
    printf("number of assigned net : %d\n", assigned_count);
    return 0;
}

