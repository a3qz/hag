#include <ncurses.h>
#include "list.h"
#include "player.h"
#include "item.h"
#include "colors.h"
#include "floor.h"
#include "gui.h"
#include <time.h>

/* TODO: don't do this, instead have a getter function */
extern char *potiontypes[];

static list_t *item_list = 0;
static item_t *held = 0;


item_t *item_add(list_t *list, int y, int x)
{
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

    if (rand() % 2) {
        item->power = rand() % (10 * (floor_get() + 1));
        item->stat = rand() % 3 + 1;
        item->type = SWORD;
        item->ident = 0;
        if (item->stat == 1) {
            item->pic = '/' | COLORS_GREEN | A_BOLD;
        } else if (item->stat == 2) {
            item->pic = ')' | COLORS_GREEN | A_BOLD;
        } else{
            item->pic = '%' | COLORS_GREEN | A_BOLD;
        }
    } else {
        item->power = rand() % (10 * (floor_get() + 1)) - (5 * (floor_get() + 1));
        item->type = POTION;
        item->stat = rand() % 6;
        item->pic = '&' | COLORS_CYAN | A_BOLD;
        item->ident = 0;
    }
    item->node = list_add_tail(list, item);
    return item;
}

item_t *item_at(int y, int x)
{
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

void item_set_list(list_t *list)
{
    item_list = list;
}

void item_inspect(item_t* item)
{
    int count = get_player_obj()->potion_count;
    int level = get_player_obj()->current_level;
    char msg[80];
    if (item && item->type == POTION) {
        switch (item->ident) {
        case -1:
            add_action("The potion remains unknown");
            break;
        case 0:
            if ((count + level) < rand() % 25) {
                add_action("The potion is unknowable");
                item->ident = -1;
            } else {
                sprintf(msg, "You discover a %s potion", potiontypes[item->stat]);
                add_action(msg);
                item->ident = 1;
            }
            break;
        case 1:
            sprintf(msg, "This is a %s potion", potiontypes[item->stat]);
            add_action(msg);
            break;
        }
    }
}

void item_drink(item_t* item)
{
    char* pts;
    char msg[80];
    if (item && item->type == POTION) {
        list_remove(item->node);
        add_action("Drank a potion");
        get_player_obj()->potion_count += 1;

        if (item->power == 1) {
            pts = "point";
        } else {
            pts = "points";
        }

        switch (item->stat) {
        case 0:     /* str */
            if (item->power > 0) {
                sprintf(msg, "It increased your strength by %d %s", item->power, pts);
                add_action(msg);
            } else if (item->power < 0) {
                sprintf(msg, "It decreased your strength by %d %s", -item->power, pts);
                add_action(msg);
            } else {
                add_action("It did nothing.");
            }
            get_player_obj()->strength += item->power;
            if (get_player_obj()->strength < 1) {
                get_player_obj()->strength = 1;
            }
            break;
        case 1:     /* dex */
            if (item->power > 0) {
                sprintf(msg, "It increased your dexterity by %d %s", item->power, pts);
                add_action(msg);
            } else if (item->power < 0) {
                sprintf(msg, "It decreased your dexterity by %d %s", -item->power, pts);
                add_action(msg);
            } else {
                add_action("It did nothing.");
            }
            get_player_obj()->dexterity += item->power;
            if (get_player_obj()->dexterity < 1) {
                get_player_obj()->dexterity = 1;
            }
            break;
        case 2:     /* int */
            if (item->power > 0) {
                sprintf(msg, "It increased your intelligence by %d %s", item->power, pts);
                add_action(msg);
            } else if (item->power < 0) {
                sprintf(msg, "It decreased your intelligence by %d %s", -item->power, pts);
                add_action(msg);
            } else {
                add_action("It did nothing.");
            }
            get_player_obj()->intelligence += item->power;
            if (get_player_obj()->intelligence < 1) {
                get_player_obj()->intelligence = 1;
            }
            break;
        case 3:     /* hp */
            item->power /= 3;
            get_player_obj()->max_hp += item->power;
            get_player_obj()->current_hp += item->power;
            if (item->power > 0) {
                sprintf(msg, "It increased your health by %d %s", item->power, pts);
                add_action(msg);
            } else if (item->power < 0) {
                sprintf(msg, "It decreased your health by %d %s", -item->power, pts);
                add_action(msg);
            } else {
                add_action("It did nothing.");
            }
            break;
        case 4:     /* luck */
            if (item->power > 0) {
                sprintf(msg, "It increased your luck by %d %s", 100 * item->power, pts);
                add_action(msg);
            } else if (item->power < 0) {
                sprintf(msg, "It decreased your luck by %d %s", -100 * item->power, pts);
                add_action(msg);
            } else {
                add_action("It did nothing.");
            }
            get_player_obj()->luck += item->power * 100;
            if (get_player_obj()->luck < 2) {
                get_player_obj()->luck = 2;
            }
            break;
        case 5:     /* exp */
        default:
            add_action("It gave you new life experiences");
            if (item->power > 0) {
                player_gain_exp(item->power);
            } else {
                player_gain_exp(item->power * -2 + 1);
            }
            break;
        }
    }
}

void item_swap(item_t* item)
{
    if (item && held && item->type == SWORD) {
        held->y = item->y;
        held->x = item->x;
        held->node = list_add_tail(item_list, held);
        list_remove(item->node);
        item->node = 0;
        held = item;
    }
}

void item_give()
{
    if (held) {
        free(held);
    }
    held = malloc(sizeof(*held));
    held->power = 0;
    held->pic = '/' | COLORS_GREEN | A_BOLD;
    held->stat = 1;
    held->node = 0;
}

void item_draw(WINDOW *win, int y, int x)
{
    int w;
    int h;
    int x0;
    int y0;
    int ex;
    int ey;
    int visible;
    item_t *e;
    if (!item_list) return;
    getmaxyx(win, h, w); /*MACRO, changes w and h */
    y0 = y - (h / 2);
    x0 = x - (w / 2);
    list_traverse(item_list->head);
    while ((e = list_traverse(0))) {
        ey = e->y - y0;
        ex = e->x - x0;
        visible = map_visible(e->y, e->x);
        if (ey >= 0 && ex >= 0 && ey < h && ex < w && visible) {
            mvwaddch(win, ey, ex, e->pic);
        }
    }
}

int item_power()
{
    if (held) {
        return held->power;
    } else {
        return 0;
    }
}

int item_stat()
{
    if (held) {
        return held->stat;
    } else {
        return 0;
    }
}

list_t * get_item_list()
{
    return item_list;
}
