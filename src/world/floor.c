#include <ncurses.h>
#include <stdio.h>
#include "floor.h"
#include "list.h"
#include "colors.h"
#include "item.h"
#include "enemy.h"
#include "enemy_rulebook.h"
#include "player.h"

#define MAX_FLOOR_TICK 10000

static int connectpoints(map_t board, int newcenterx, int newcentery,
                         int oldcenterx, int oldcentery);

static const int NUM_ROOMS = 30;
static const int MAX_ROOM_X = 30;
static const int MAX_ROOM_Y = 30;
static const int BOARD_X = 400;
static const int BOARD_Y = 400;

static floor_t floors[FLOOR_COUNT] = { 0 };

static int current_floor = -1;

static void floor_init(void)
{
    int type;
    enemy_t* e;
    enemy_template_t en;
    int xpos;
    int ypos;
    int i;
    int j;
    int up_y;
    int up_x;
    int down_y;
    int down_x;
    int room_iterator;
    int xlen = 20;
    int ylen = 20;
    int xcenter = 0;
    int ycenter = 0;
    int xcenter2 = 0;
    int ycenter2 = 0;
    map_t board;
    list_t *enemies;
    list_t *items;

    if (current_floor < FLOOR_COUNT && current_floor >= 0
        && !floors[current_floor].loaded) {
        board = (map_t)malloc(BOARD_Y * sizeof(map_row_t));
        enemies = list_create();
        items = list_create();


        for (i = 0; i < BOARD_Y; i++) {
            board[i] = (map_row_t)malloc(BOARD_X * sizeof(map_space_t));
        }

        for (i = 0; i < BOARD_Y; i++) {
            for (j = 0; j < BOARD_X; j++) {
                board[i][j] = '#' | COLORS_BLACK;
            }
        }

        if (floor_get() != FLOOR_COUNT - 1) {
            for (room_iterator = 0; room_iterator < NUM_ROOMS;
                 room_iterator++) {
                ylen = rand() % MAX_ROOM_Y + 1;
                xlen = rand() % MAX_ROOM_X + 1;

                ypos = rand() % (BOARD_Y - ylen - 2) + 1;
                xpos = rand() % (BOARD_X - xlen - 2) + 1;

                xcenter = xpos + xlen / 2;
                ycenter = ypos + ylen / 2;

                for (i = 0; i < ylen; i++) {
                    for (j = 0; j < xlen; j++) {
                        board[i + ypos][j + xpos] =
                            '.' | A_DIM | COLORS_BLACK;
                        board[i + ypos][j + xpos] =
                            '.' | A_DIM | COLORS_BLACK;
                        if (rand() % (2000 + 1) <= 2 * (floor_get() + 5)) {
                            type =
                                rand() %
                                ((floor_get() < 3) ? 2 : floor_get());
                            en = get_rulebook()[type];
                            enemy_add(enemies, type, en.pic,
                                      en.base_hp +
                                      (((floor_get())) * en.base_hp) / 4,
                                      i + ypos, j + xpos,
                                      en.base_sight_range,
                                      en.base_strength +
                                      rand() % (floor_get() + 1),
                                      en.base_speed,
                                      en.base_exp, en.name);
                        }
                        if (rand() % (8000 + 1) <= 2 * (floor_get() + 5)) {
                            item_add(items, i + ypos, j + xpos);
                        }
                    }
                }

                if (xcenter2 != 0) {
                    connectpoints(board, ycenter, xcenter, ycenter2,
                                  xcenter2);
                }
                xcenter2 = xcenter;
                ycenter2 = ycenter;

                if (room_iterator == 0) {
                    up_x = xpos + rand() % (xlen);
                    up_y = ypos + rand() % (ylen);
                    list_traverse(enemies->head);
                    while ((e = list_traverse(0))) {
                        if (e->y == up_y && e->x == up_x) {
                            up_x = xpos + rand() % (xlen);
                            up_y = ypos + rand() % (ylen);
                            list_traverse(enemies->head);
                        }
                    }
                } else if (room_iterator == NUM_ROOMS - 1) {
                    down_x = xpos + rand() % (xlen);
                    down_y = ypos + rand() % (ylen);
                    list_traverse(enemies->head);
                    while ((e = list_traverse(0))) {
                        if (e->y == down_y && e->x == down_x) {
                            down_x = xpos + rand() % (xlen);
                            down_y = ypos + rand() % (ylen);
                            list_traverse(enemies->head);
                        }
                    }
                }
            }

            board[down_y][down_x] = '>' | A_BOLD | COLORS_BLUE;
            if (floor_get() > 0) {
                board[up_y][up_x] = '<' | A_BOLD | COLORS_BLUE;
            }
        } else {
            up_x = 150;
            up_y = 150;
            down_x = up_x;
            down_y = up_y + 40;
            type = enemy_index_hag();
            en = get_rulebook()[type];
            enemy_add(enemies, type, en.pic, en.base_hp, down_y, down_x,
                      en.base_sight_range, en.base_strength, en.base_speed,
                      en.base_exp, en.name);
            xpos = down_x - 10;
            ypos = down_y - 10;
            for (i = 0; i < ylen; i++) {
                for (j = 0; j < xlen; j++) {
                    board[i + ypos][j + xpos] = '.' | A_DIM | COLORS_BLACK;
                    board[i + ypos][j + xpos] = '.' | A_DIM | COLORS_BLACK;
                }
            }
            connectpoints(board, down_y, down_x, up_y, up_x);
            board[up_y][up_x] = '<' | A_BOLD | COLORS_BLUE;
        }

        floors[current_floor].map = board;
        floors[current_floor].up_x = up_x;
        floors[current_floor].up_y = up_y;
        floors[current_floor].down_x = down_x;
        floors[current_floor].down_y = down_y;
        floors[current_floor].enemy_list = enemies;
        floors[current_floor].item_list = items;
        floors[current_floor].loaded = 1;
        floors[current_floor].floor_tick = 0;
    }
}

void floor_goto(int f)
{
    if (f < FLOOR_COUNT && f >= 0) {
        current_floor = f;
        floor_init();
        item_set_list(floors[current_floor].item_list);
        enemy_set(floors[current_floor].enemy_list);
        map_load(floors[current_floor].map, BOARD_X, BOARD_Y);
    }
}

int floor_get()
{
    return current_floor;
}

void floor_down()
{
    floor_goto(current_floor + 1);
    set_player_y(floors[current_floor].up_y);
    set_player_x(floors[current_floor].up_x);
}

void floor_up()
{
    floor_goto(current_floor - 1);
    set_player_y(floors[current_floor].down_y);
    set_player_x(floors[current_floor].down_x);
}

static int connectpoints(map_t board, int newcentery, int newcenterx,
                         int oldcentery, int oldcenterx)
{
    int xdiff = newcenterx - oldcenterx;
    int ydiff = newcentery - oldcentery;
    int realx = newcenterx;
    int realy = newcentery;

    while (abs(xdiff) > 0 || abs(ydiff) > 0) {
        if (abs(xdiff) > abs(ydiff)) {
            if (xdiff > 0) {
                xdiff -= 1;
                realx -= 1;
            } else if (xdiff < 0) {
                xdiff += 1;
                realx += 1;
            }
            board[realy][realx] = '.' | A_DIM | COLORS_BLACK;
        } else {
            if (ydiff > 0) {
                ydiff -= 1;
                realy -= 1;
            } else if (ydiff < 0) {
                ydiff += 1;
                realy += 1;
            }
            board[realy][realx] = '.' | A_DIM | COLORS_BLACK;
        }
    }
    return 0;
}

int floor_up_xcoord()
{
    return floors[current_floor].up_x;
}

int floor_up_ycoord()
{
    return floors[current_floor].up_y;
}

int floor_down_xcoord()
{
    return floors[current_floor].down_x;
}

int floor_down_ycoord()
{
    return floors[current_floor].down_y;
}

int floor_tick()
{
    floors[current_floor].floor_tick++;
    if (floors[current_floor].floor_tick == MAX_FLOOR_TICK) {
        return 2;
    } else if (floors[current_floor].floor_tick > MAX_FLOOR_TICK) {
        player_hurt(1);
        return 1;
    } else {
        return 0;
    }
}

int floor_tick_get()
{
    return floors[current_floor].floor_tick;
}
