#include <ncurses.h>
#include "list.h"
#include "player.h"
#include "item.h"
#include "colors.h"
#include "floor.h"
#include "gui.h"
#include <time.h>

static list_t *item_list = 0;
static item_t *held = 0;


item_t *item_add(list_t *list, int y, int x) {
    item_t *item;
    if (!list) {
        if (item_list) {
            list = item_list;
        } else {
            return 0;
        }
    }
    item = malloc(sizeof(*item));
    item->y = y;
    item->x = x;

    if (rand()%2) {
        item->power = rand()%(10*(floor_get()+1));
        item->stat = rand()%3 + 1;
        item->type = SWORD;
        if(item->stat == 1){
            item->pic = '/'|COLORS_GREEN|A_BOLD;
        } else if(item->stat == 2){
            item->pic = ')'|COLORS_GREEN|A_BOLD;
        } else{
            item->pic = '%'|COLORS_GREEN|A_BOLD;
        }
    } else {
        item->power = rand()%(10*(floor_get()+1)) - (5*(floor_get()+1));
        item->type = POTION;
        item->stat = rand()%6;
        item->pic = '&'|COLORS_CYAN|A_BOLD;
    }
    item->node = list_add_tail(list, item);
    return item;
}

item_t *item_at(int y, int x) {
    item_t *t;
    if (!item_list) {
        return 0;
    }
    list_traverse(item_list->head);
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

void item_drink(item_t* item) {
    char msg[80];
    if (item && item->type == POTION) {
        list_remove(item->node);
        add_action("Drank a potion");
        switch (item->stat) {
            case 0: /* str */
                if (item->power > 0) {
                    sprintf(msg, "It increased your strength by %d points", item->power);
                    add_action(msg);
                } else if (item->power < 0) {
                    sprintf(msg, "It decreased your strength by %d points", -item->power);
                    add_action(msg);
                } else {
                    add_action("It did nothing.");
                }
                get_player_obj()->strength += item->power;
                if (get_player_obj()->strength < 1) {
                    get_player_obj()->strength = 1;
                }
                break;
            case 1: /* dex */
                if (item->power > 0) {
                    sprintf(msg, "It increased your dexterity by %d points", item->power);
                    add_action(msg);
                } else if (item->power < 0) {
                    sprintf(msg, "It decreased your dexterity by %d points", -item->power);
                    add_action(msg);
                } else {
                    add_action("It did nothing.");
                }
                get_player_obj()->dexterity += item->power;
                if (get_player_obj()->dexterity < 1) {
                    get_player_obj()->dexterity = 1;
                }
                break;
            case 2: /* int */
                if (item->power > 0) {
                    sprintf(msg, "It increased your intelligence by %d points", item->power);
                    add_action(msg);
                } else if (item->power < 0) {
                    sprintf(msg, "It decreased your intelligence by %d points", -item->power);
                    add_action(msg);
                } else {
                    add_action("It did nothing.");
                }
                get_player_obj()->intelligence += item->power;
                if (get_player_obj()->intelligence < 1) {
                    get_player_obj()->intelligence = 1;
                }
                break;
            case 3: /* hp */
                item->power /= 3;
                get_player_obj()->max_hp += item->power;
                get_player_obj()->current_hp += item->power;
                if (item->power > 0) {
                    sprintf(msg, "It increased your health by %d points", item->power);
                    add_action(msg);
                } else if (item->power < 0) {
                    sprintf(msg, "It decreased your health by %d points", -item->power);
                    add_action(msg);
                } else {
                    add_action("It did nothing.");
                }
                break;
            case 4: /* luck */
                if (item->power > 0) {
                    sprintf(msg, "It increased your luck by %d points", item->power*100);
                    add_action(msg);
                } else if (item->power < 0) {
                    sprintf(msg, "It decreased your luck by %d points", -item->power*100);
                    add_action(msg);
                } else {
                    add_action("It did nothing.");
                }
                get_player_obj()->luck += item->power*100;
                if(get_player_obj()->luck < 2){
                    get_player_obj()->luck = 2;
                }
                break;
            case 5: /* exp */
            default:
                add_action("It gave you new life experiences");
                if (item->power > 0) {
                    player_gain_exp(item->power);
                } else {
                    player_gain_exp(item->power*-2 + 1);
                }
                break;
        }
    }
}

void item_swap(item_t* item) {
    if (item && held && item->type == SWORD) {
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
    int w;
    int h;
    int x0;
    int y0;
    int ex;
    int ey;
    item_t *e;
    if (!item_list) return;
    getmaxyx(win, h, w); /*MACRO, changes w and h */
    y0 = y - (h/2);
    x0 = x - (w/2);
    list_traverse(item_list->head);
    while ((e = list_traverse(0))) {
        ey = e->y - y0;
        ex = e->x - x0;
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
