#ifndef ITEM_H
#define ITEM_H
#include <ncurses.h>
#include "../util/list.h"
typedef struct item {
    int y;
    int x;
    int power;
    int stat;
    int pic;
    int ident;
    enum {
        SWORD, POTION
    } type;
    node_t *node;
} item_t;

item_t *item_add(list_t * list, int y, int x);
item_t *item_at(int y, int x);
void item_set_list(list_t * list);
void item_swap(item_t * item);
void item_drink(item_t * item);
void item_draw(WINDOW * win, int y, int x);
void item_inspect(item_t* item);
void item_give(void);
int item_power(void);
int item_stat(void);
list_t *get_item_list(void);
#endif
