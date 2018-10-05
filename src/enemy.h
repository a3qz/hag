#ifndef ENEMY_H
#define ENEMY_H
    #include <ncurses.h>
    #include "list.h"
    typedef struct enemy {
        int type;
        int pic;
        int hp;
        int y;
        int x;
        int sight_range;
        int strength;
		int xp;
        char *name;
        node_t *node;
    } enemy_t;

    enemy_t *enemy_add(list_t *floor_enemy_list, int type, int pic, int hp, int y, int x, int sight_range, int strength, int xp, char *name);
    enemy_t *enemy_at(int y, int x);
    void enemy_set(list_t *list);
    void enemy_hurt(enemy_t *e, int d);
    void enemy_draw(WINDOW *win, int y, int x);
    void enemy_clear();
    void enemy_turn_driver(WINDOW *win, int y, int x);
	list_t * get_enemy_list();
#endif
