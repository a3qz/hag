#ifndef FLOOR_H
#define FLOOR_H

    #define FLOOR_COUNT 10
    
    #include "list.h"
    #include "map.h"

    typedef struct floor {
        int loaded;
        list_t *enemy_list;
        map_t map;
        int down_y;
        int down_x;
        int up_y;
        int up_x;
    } floor_t;

    void floor_init();
    void floor_goto(int f);
    void floor_down();
    void floor_up();
    int floor_get();

#endif
