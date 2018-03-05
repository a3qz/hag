#include <ncurses.h>
#include "list.h"
#include "item.h"
#include "colors.h"
#include "floor.h"
#include <time.h>

static list_t *item_list = 0;
static item_t *held = 0;


item_t *item_add(list_t *list, int y, int x) {
	if (!list) {
        if (item_list) {
            list = item_list;
        } else {
            return 0;
        }
    }
    
    item_t *item = malloc(sizeof(*item));
    item->y = y;
    item->x = x;
    item->power = rand()%(10*(floor_get()+1));
	item->stat = rand()%3 + 1;
	if(item->stat == 1){
		item->pic = '/'|COLORS_GREEN|A_BOLD;
	} else if(item->stat == 2){
		item->pic = ')'|COLORS_GREEN|A_BOLD;
	} else{
		item->pic = '%'|COLORS_GREEN|A_BOLD;
	}
    item->node = list_add_tail(list, item);
    return item;
}

item_t *item_at(int y, int x) {
    if (!item_list) {
        return 0;
    }
    list_traverse(item_list->head);
    item_t *t;
    while ((t = list_traverse(0))) {
        if (t->y == y && t->x == x) {
            return t;
        }
    } 
    return 0;
}

void item_set_list(list_t *list) {
    item_list = list;
}

void item_swap(item_t* item) {
    if (item && held) {
        held->y = item->y;
        held->x = item->x;
        held->node = list_add_tail(item_list, held);
        list_remove(item->node);
        item->node = 0;
        held = item;
    }
}

void item_give() {
    if (held) {
        free(held);
    }
    held = malloc(sizeof(*held));
    held->power = 0;
	held->pic = '/'|COLORS_GREEN|A_BOLD;
	held->stat = 1;
    held->node = 0;
}

void item_draw(WINDOW *win, int y, int x) {
    if (!item_list) return;
    int w, h;
    getmaxyx(win, h, w); /*MACRO, changes w and h */
    int y0 = y - (h/2);
    int x0 = x - (w/2);
    list_traverse(item_list->head);
    item_t *e;
    while ((e = list_traverse(0))) {
        int ey = e->y - y0;
        int ex = e->x - x0;
        if (ey >= 0 && ex >= 0 && ey < h && ex < w) {
            mvwaddch(win, ey, ex, e->pic);
        }
    } 
}

int item_power() {
    if (held) {
        return held->power;
    } else {
        return 0;
    }
}   

int item_stat(){
	if (held) {
        return held->stat;
    } else {
        return 0;
    }
}

list_t * get_item_list(){
	return item_list;
}