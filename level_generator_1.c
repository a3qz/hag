#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "level_generator_1.h"

int testmain(){
    int NUM_ROOMS = 30;
    int MAX_ROOM_X = 30;
    int MIN_ROOM_X = 3;
    int MAX_ROOM_Y = 30;
    int MIN_ROOM_Y = 3;
    int BOARD_X = 100;
    int BOARD_Y = 200;
    char ** x = createmap(NUM_ROOMS, MAX_ROOM_X, MIN_ROOM_X, MAX_ROOM_Y, MIN_ROOM_Y, BOARD_X, BOARD_Y);
    return 0;
}
char ** createmap(int NUM_ROOMS, int MAX_ROOM_X, int MIN_ROOM_X, int MAX_ROOM_Y, int MIN_ROOM_Y, int BOARD_X, int BOARD_Y){
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
            }
        }

        if(xcenter2 != 0){
            // call connectpoints
            connectpoints(board, xcenter, ycenter, xcenter2, ycenter2);
        }
        xcenter2 = xcenter;
        ycenter2 = ycenter;
    }
    
    /*for (i = 0; i < BOARD_X; i++){
        for(j = 0; j < BOARD_Y; j++){
            printf("%c", board[i][j]);
        }
        printf("\n");
    }*/
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
        } else {
            if(ydiff > 0){
                ydiff -= 1;
                realy -= 1;
            } else if(ydiff < 0){
                ydiff += 1;
                realy += 1;
            }
            board[realx][realy] = '.';
        }
    }
    
}

