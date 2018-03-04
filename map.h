#ifndef MAP_H
#define MAP_H
    #include <ncurses.h>

    typedef int          map_space_t;
    typedef map_space_t* map_row_t;
    typedef map_row_t*   map_t;

    void map_load(map_t new_map, int w, int h);
    void map_set(char c, int y, int x);
    char map_get(int y, int x);
    void map_print(WINDOW *win, int y, int x);
    int map_width();
    int map_height();
    void map_line(int newcentery, int newcenterx, int oldcentery, int oldcenterx);

#endif
