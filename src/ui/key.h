#ifndef KEY_H
#define KEY_H


#include "../util/list.h"
#include "../world/map.h"
typedef struct key_item {
    char *name;
    int pic;
    char extra_info[100];
    node_t *node;
} key_item_t;

void key_setup(void);
void key_add_stair(int dir, int pic);
list_t *key_get_list(void);
void key_checker(WINDOW * win, int y, int x);
#endif
