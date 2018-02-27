#include "enemy.h"
#include "list.h"
#include "map.h"
#include "stdlib.h"

static list_t *enemy_list = 0;

enemy_t *enemy_add(int type, char pic, int hp, int y, int x, int sight_range) {
    if (!enemy_list) {
        enemy_list = list_create();
    }
    enemy_t *e = (enemy_t*)malloc(sizeof(*e));
    e->type = type;
    e->pic = pic;
    e->hp = hp;
    e->y = y;
    e->x = x;
    e->sight_range = sight_range;
    e->node = list_add_tail(enemy_list, e);
}

enemy_t *enemy_at(int y, int x) {
    if (!enemy_list) {
        return 0;
    }
    list_traverse(enemy_list->head);
    enemy_t *e;
    while (e = list_traverse(0)) {
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
    while (e = list_traverse(0)) {
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
    while (e = list_traverse(0)) {
        enemy_take_turn(e, win, y, x);
    } 
}

void enemy_take_turn(enemy_t *e, WINDOW *win, int y, int x){
    // movement
    int w, h;
    getmaxyx(win, h, w); //MACRO, changes w and h
    int y0 = y - (h/2);
    int x0 = x - (w/2);
    int ey = e->y - y0;
    int ex = e->x - x0;
    int yn = e->y;
    int xn = e->x;
    
    if (ey >= 0 && ex >= 0 && ey < h && ex < w) {  // if the enemy is on screen
         // TODO attacking
        
        // if enemy is in range of the player
        int ydiff = e->y - y;
        int xdiff = e->x - x;
        if(abs(ydiff) < e->sight_range && abs(xdiff) < e->sight_range){
                if(ydiff < 0){
                    yn++;
                } else if (ydiff > 0){
                    yn--;
                } else{

                }
                if (xdiff < 0){
                    xn++;
                } else if (xdiff > 0){
                    xn--;
                } else {

                }
                if(map_get(yn, xn) == '.'){
                    e->y = yn;
                    e->x = xn;
                } else if (map_get(yn, e->x) == '.'){
                    e->y = yn;
                } else if (map_get(e->y, xn) == '.'){
                    e->x = xn;
                }
        }
    }
   
}