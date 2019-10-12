#ifndef FLOOR_H
#define FLOOR_H

#define FLOOR_COUNT 10

#include "list.h"
#include "map.h"

typedef struct floor {
    int loaded;
    unsigned int floor_tick;
    list_t *enemy_list;
    list_t *item_list;
    map_t map;
    int down_y;
    int down_x;
    int up_y;
    int up_x;
} floor_t;

void floor_goto(int f);
void floor_down(void);
void floor_up(void);
int floor_get(void);
int floor_up_xcoord(void);
int floor_up_ycoord(void);
int floor_down_xcoord(void);
int floor_down_ycoord(void);
int floor_tick(void);
int floor_tick_get(void);
#endif
