#ifndef MAP_H
#define MAP_H
    #include <ncurses.h>

    void map_load(char **new_map, int w, int h);
    void map_set(char c, int y, int x);
    char map_get(int y, int x);
    void map_print(WINDOW *win, int y, int x);
#endif
