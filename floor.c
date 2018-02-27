#include <ncurses.h>
#include "floor.h"
#include "list.h"

static const int NUM_ROOMS = 30;
static const int MAX_ROOM_X = 30;
static const int MIN_ROOM_X = 3;
static const int MAX_ROOM_Y = 30;
static const int MIN_ROOM_Y = 3;
static const int BOARD_X = 100;
static const int BOARD_Y = 200;

static floor_t floors[FLOOR_COUNT] = {0};

static int current_floor = 0;

void floor_init() {
    if (current_floor < FLOOR_COUNT && current_floor >= 0 && !floors[current_floor].loaded) {
        floors[current_floor].map = createmap(NUM_ROOMS, MAX_ROOM_X, MIN_ROOM_X, MAX_ROOM_Y, MIN_ROOM_Y, BOARD_Y, BOARD_X);
        floors[current_floor].enemy_list = list_create();
        floors[current_floor].loaded = 1;
        floors[current_floor].down_y = floors[current_floor].down_x = 0;
        floors[current_floor].up_y = floors[current_floor].up_x = 0;
    }
}

void floor_goto(int f) {
    if (current_floor < FLOOR_COUNT && current_floor >= 0 && !floors[current_floor].loaded) {
        current_floor = f;
        floor_init();
        enemy_set(floors[current_floor].enemy_list);
        map_load(floots[current_floor].map, BOARD_X, BOARD_Y);
    }
}

int floor_get() {
    return current_floor;
}

void floor_down() {
    floor_goto(current_floor-1);
    //set player coordinates here
}

void floor_up() {
    floor_goto(current_floor+1);
    //set player coordinates here
}
