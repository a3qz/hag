#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "map.h"
#include "level_generator_1.h"
#include "enemy.h"
#include "floor.h"
#include "list.h"

int period_count = 0;

int testmain(){
    int NUM_ROOMS = 30;
    int MAX_ROOM_X = 30;
    int MIN_ROOM_X = 3;
    int MAX_ROOM_Y = 30;
    int MIN_ROOM_Y = 3;
    int BOARD_X = 100;
    int BOARD_Y = 200;
    //map_t x = createmap(NUM_ROOMS, MAX_ROOM_X, MIN_ROOM_X, MAX_ROOM_Y, MIN_ROOM_Y, BOARD_X, BOARD_Y, 0, 0, 0, 0);
    return 0;
}
map_t createmap(int NUM_ROOMS, int MAX_ROOM_X, int MIN_ROOM_X, int MAX_ROOM_Y, int MIN_ROOM_Y, int BOARD_X, int BOARD_Y, int* DOWN_Y, int* DOWN_X, int* UP_Y, int* UP_X){
    srand(time(0)); 
            
    char **board = (char **)malloc(BOARD_X *BOARD_Y * sizeof(char*));
    int i, j;

    for(i = 0; i < BOARD_X; i++){
        board[i] = (char *)malloc(BOARD_Y * sizeof(char));
    }

    for (i = 0; i < BOARD_X; i++){
        for(j = 0; j < BOARD_Y; j++){
            board[i][j] = '#';
        }
    }

    int xcenter = 0;
    int ycenter = 0;
    int xcenter2 = 0;
    int ycenter2 = 0;
    int room_iterator;
    int up_y;
    int up_x;
    int down_y;
    int down_x;
    
    int num_enemies = 3*(floor_get()+4);

    
    list_t *enemies = list_create();


    for(room_iterator=0; room_iterator < NUM_ROOMS; room_iterator++){
        int xlen = rand()%MAX_ROOM_X;
        int ylen = rand()%MAX_ROOM_Y;

        int xpos = rand()%(BOARD_X-xlen-2)+1;
        int ypos = rand()%(BOARD_Y-ylen-2)+1;

        xcenter = xpos+xlen/2;
        ycenter = ypos+ylen/2;
        
        for(i = 0; i < xlen; i++){
            for(j=0; j < ylen; j++){
                board[i+xpos][j+ypos] = '.';
                period_count++;
                if(rand()%(2000+1) <= 2*(floor_get()+5)){
                    enemy_add(enemies, 0, 'X', 20, i+xpos, j+ypos, 10, 5);
                }
            }
        }

        if(xcenter2 != 0){
            // call connectpoints
            connectpoints(board, xcenter, ycenter, xcenter2, ycenter2);
        }
        xcenter2 = xcenter;
        ycenter2 = ycenter;

        if (room_iterator == 0) {
            up_y = xpos + rand()%(xlen+1);
            up_x = ypos + rand()%(ylen+1);
            if (UP_X) {
                *UP_X = up_x;
            }
            if (UP_Y) {
                *UP_Y = up_y;
            }
        } else if (room_iterator == NUM_ROOMS-1) {
            down_y = xpos + rand()%(xlen+1);
            down_x = ypos + rand()%(ylen+1);
            if (DOWN_X) {
                *DOWN_X = down_x;
            }
            if (DOWN_Y) {
                *DOWN_Y = down_y;
            }
        }
    }
    board[down_y][down_x] = '>';
    board[up_y][up_x] = '<';
    
    /*for (i = 0; i < BOARD_X; i++){
        for(j = 0; j < BOARD_Y; j++){
            printf("%c", board[i][j]);
        }
        printf("\n");
    }*/
    floor_add_enemy_list(enemies);
    
    return board;
}

int connectpoints(char ** board, int newcenterx, int newcentery, int oldcenterx, int oldcentery){
    int xdiff = newcenterx-oldcenterx;
    int ydiff = newcentery-oldcentery;
    int realx = newcenterx;
    int realy = newcentery;
    
    while(abs(xdiff) > 0 || abs(ydiff) > 0){
        if(abs(xdiff) > abs(ydiff)){
            if(xdiff > 0){
                xdiff -= 1;
                realx -= 1;
            } else if(xdiff < 0){
                xdiff += 1;
                realx += 1;
            }
            board[realx][realy] = '.';
            period_count++;
        } else {
            if(ydiff > 0){
                ydiff -= 1;
                realy -= 1;
            } else if(ydiff < 0){
                ydiff += 1;
                realy += 1;
            }
            board[realx][realy] = '.';
            period_count++;
        }
    }
	return 0;  
}

