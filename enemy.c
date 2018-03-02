#include "enemy.h"
#include "enemy_rulebook.h"
#include "list.h"
#include "map.h"
#include "stdlib.h"
#include "player.h"

static list_t *enemy_list = 0;

void enemy_set(list_t *list) {
    enemy_list = list;
}

enemy_t *enemy_add(list_t *floor_enemy_list, int type, int pic, int hp, int y, int x, int sight_range, int strength, int xp) {
    if (!floor_enemy_list) {
        if (enemy_list) {
            floor_enemy_list = enemy_list;
        } else {
            return 0;
        }
    }
    enemy_t *e = (enemy_t*)malloc(sizeof(*e));
    e->type = type;
    e->pic = pic;
    e->hp = hp;
    e->y = y;
    e->x = x;
    e->sight_range = sight_range;
    e->strength = strength;
	e->xp = xp;
    e->node = list_add_tail(floor_enemy_list, e);
    return e;
}

enemy_t *enemy_at(int y, int x) {
    if (!enemy_list) {
        return 0;
    }
    list_traverse(enemy_list->head);
    enemy_t *e;
    while ((e = list_traverse(0))) {
        if (e->y == y && e->x == x) {
            return e;
        }
    } 
    return 0;
}

void enemy_hurt(enemy_t *e, int d) {
    if (!e) return;

    e->hp -= d;
    if (e->hp <= 0) {
		player_gain_exp(e->xp);
        list_remove(e->node);
        free(e);
    }
}

void enemy_draw(WINDOW *win, int y, int x) {
    if (!enemy_list) return;
    int w, h;
    getmaxyx(win, h, w); //MACRO, changes w and h
    int y0 = y - (h/2);
    int x0 = x - (w/2);
    list_traverse(enemy_list->head);
    enemy_t *e;
    while ((e = list_traverse(0))) {
        int ey = e->y - y0;
        int ex = e->x - x0;
        if (ey >= 0 && ex >= 0 && ey < h && ex < w) {
            mvwaddch(win, ey, ex, e->pic);
        }
    } 
}

void enemy_clear() {
    if (!enemy_list) return;
    while (enemy_list->head) {
        free(enemy_list->head->data);
        node_t *t = enemy_list->head;
        enemy_list->head = enemy_list->head->next;
        free(t);
    }
    enemy_list->tail = 0;
}

void enemy_turn_driver(WINDOW *win, int y, int x){
    list_traverse(enemy_list->head);
    enemy_t *e;
    while ((e = list_traverse(0))) {
        enemy_take_turn(e, win, y, x);
    } 
}

