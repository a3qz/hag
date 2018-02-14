#include <ncurses.h>

#include "map.h"

static char *map = 0;
static int width = 0;
static int height = 0;

static int in_bounds(int y, int x) {
    return y>=0 && x>=0 && y<height && x<width;
}

void map_load(char *new_map, int w, int h) {
    map = new_map;
    width = w;
    height = h; 
}

void map_set(char c, int y, int x) {
    if (in_bounds(y, x) && map) {
        map[x + y*width] = c;
    }
}

char map_get(int y, int x) {
    if (in_bounds(y, x) && map) {
        return map[x + y*width];
    } else {
        return 0;
    }
}

void map_print(WINDOW *win, int y, int x) {
    if (win && map && in_bounds(y, x)) {
        int w, h;
        getmaxyx(win, h, w); //MACRO, changes w and h
        int y0 = y - (h/2);
        int x0 = x - (w/2);
        int y1 = y + (h/2);
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
            mvwaddnstr(win, i, j, map + x0 + y0*width, w);
            y0++;
        }
    }
}
