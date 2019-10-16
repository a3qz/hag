#include "enemy.h"
#include "enemy_rulebook.h"
#include "list.h"
#include "map.h"
#include "gui.h"
#include "stdlib.h"
#include "player.h"

static list_t *enemy_list = 0;

void enemy_set(list_t * list)
{
    enemy_list = list;
}

enemy_t *enemy_add(list_t * floor_enemy_list, int type, int pic, int hp,
                   int y, int x, int sight_range, int strength, int xp,
                   char *name)
{
    enemy_t *e;
    if (!floor_enemy_list) {
        if (enemy_list) {
            floor_enemy_list = enemy_list;
        } else {
            return 0;
        }
    }
    e = (enemy_t *) malloc(sizeof(*e));
    e->type = type;
    e->pic = pic;
    e->hp = hp;
    e->y = y;
    e->x = x;
    e->sight_range = sight_range;
    e->strength = strength;
    e->xp = xp;
    e->name = name;
    e->node = list_add_tail(floor_enemy_list, e);
    return e;
}

enemy_t *enemy_at(int y, int x)
{
    enemy_t *e;
    if (!enemy_list) {
        return 0;
    }
    list_traverse(enemy_list->head);
    while ((e = list_traverse(0))) {
        if (e->y == y && e->x == x) {
            return e;
        }
    }
    return 0;
}

void enemy_hurt(enemy_t * e, int d)
{
    int nx;
    int ny;
    char msg[80];
    enemy_template_t en;

    if (!e)
        return;

    if ((e->pic & A_CHARTEXT) == 'H') {
        e->hp -= 1;
        if (e->hp <= 0) {
            if (e->type == enemy_index_hag()) {
                add_action
                    ("After a fierce battle, the old hag's power wanes, and she falls to the ground, defeated.");
            } else {
                add_action
                    ("You swing at the hag, but your sword passes through, revealing that she was only a mirage.");
            }
            player_gain_exp(e->xp);
            list_remove(e->node);
            free(e);
        } else {
            if (e->hp % 3 == 0) {
                add_action
                    ("In a flash, the old hag manages to blink across the room.");
                nx = e->x + (rand() % 2 * 2 - 1) * ((rand() % 4) + 5);
                ny = e->y + (rand() % 2 * 2 - 1) * ((rand() % 4) + 5);
                map_line(e->y, e->x, ny, nx);
                if (e->hp <= 15) {
                    add_action
                        ("The old hag uses her magic to cast a doppleganger of herself!");
                    en = get_rulebook()[enemy_index_fake_hag()];
                    enemy_add(0, enemy_index_fake_hag(), en.pic,
                              en.base_hp, ny, nx, en.base_sight_range,
                              en.base_strength, en.base_exp, "Fake");
                    nx += (rand() % 2 * 2 - 1) * ((rand() % 4) + 5);
                    ny += (rand() % 2 * 2 - 1) * ((rand() % 4) + 5);
                    map_line(e->y, e->x, ny, nx);
                }
                e->x = nx;
                e->y = ny;
            }
        }
    } else {
        e->hp -= d;
        if (e->hp <= 0) {
            sprintf(msg, "You defeat the %s and gain %d experience.",
                    e->name, e->xp);
            add_action(msg);
            player_gain_exp(e->xp);
            list_remove(e->node);
            free(e);
        }
    }
}

void enemy_draw(WINDOW * win, int y, int x)
{
    int w;
    int h;
    int y0;
    int x0;
    int ey;
    int ex;
    int visible;
    enemy_t *e;

    if (!enemy_list)
        return;

    getmaxyx(win, h, w);        /*MACRO, changes w and h */
    y0 = y - (h / 2);
    x0 = x - (w / 2);
    list_traverse(enemy_list->head);
    while ((e = list_traverse(0))) {
        ey = e->y - y0;
        ex = e->x - x0;
        visible = map_visible(e->y, e->x);
        if (ey >= 0 && ex >= 0 && ey < h && ex < w && visible) {
            mvwaddch(win, ey, ex, e->pic);
        }
    }
}

void enemy_clear()
{
    node_t *t;

    if (!enemy_list)
        return;

    while (enemy_list->head) {
        free(enemy_list->head->data);
        t = enemy_list->head;
        enemy_list->head = enemy_list->head->next;
        free(t);
    }
    enemy_list->tail = 0;
}

void enemy_turn_driver(WINDOW * win, int y, int x)
{
    node_t *e = enemy_list->head;
    while (e) {
        enemy_take_turn(e->data, win, y, x);
        e = e->next;
    }
}

list_t *get_enemy_list()
{
    return enemy_list;
}
