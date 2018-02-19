#ifndef ENEMY_H
#define ENEMY_H
    #include <ncurses.h>
    #include "list.h"
    typedef struct enemy {
        int type;
        char pic;
        int hp;
        int y;
        int x;
        node_t *node;
    } enemy_t;
    enemy_t *enemy_add(int type, char pic, int hp, int y, int x);
    enemy_t *enemy_at(int y, int x);
    void enemy_hurt(enemy_t *e, int d);
    void enemy_draw(WINDOW *win, int y, int x);
    void enemy_clear();
#endif
