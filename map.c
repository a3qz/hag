#include <ncurses.h>
#include <stdlib.h>

#include "map.h"
#include "key.h"
#include "colors.h"

static map_t map = 0;
static int width = 0;
static int height = 0;

static int in_bounds(int y, int x) {
    return y>=0 && x>=0 && y<height && x<width;
}

void map_load(map_t new_map, int w, int h) {
    map = new_map;
    width = w;
    height = h; 
}

void map_set(char c, int y, int x) {
    if (in_bounds(y, x) && map) {
        map[y][x] = c;
    }
}

char map_get(int y, int x) {
    if (in_bounds(y, x) && map) {
        return map[y][x];
    } else {
        return 0;
    }
}

void map_print(WINDOW *win, int y, int x) {
    if (win && map && in_bounds(y, x)) {
        int w, h;
        getmaxyx(win, h, w); /*MACRO, changes w and h */
        int y0 = y - (h/2);
        int x0 = x - (w/2);
        int x1 = x + (w/2);
        int i = 0;
        int j = 0;
        if (y0 < 0) {
            i -= y0;
            y0 = 0;
        }
       if (x0 < 0) {
            j -= x0;
            w -= j;
            x0 = 0;
        }
        if (x1 > width) {
            w -= x1 - width;
        }
        for (; i < h && y0 < height; i++) {
            int k;
            for (k = 0; k < w && x0+k<width; k++) {
                mvwaddch(win, i, j + k, map[y0][x0+k]);
            }
            y0++;
        }
    }
}

int map_width() {
    return width;
}

int map_height() {
    return height;
}

void map_line(int newcentery, int newcenterx, int oldcentery, int oldcenterx) {
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
            map[realy][realx] = '.' | A_DIM;
        } else {
            if(ydiff > 0){
                ydiff -= 1;
                realy -= 1;
            } else if(ydiff < 0){
                ydiff += 1;
                realy += 1;
            }
            map[realy][realx] = '.' | A_DIM;
        }
    }
}
