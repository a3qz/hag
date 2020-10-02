#include "enemy_rulebook.h"
#include "enemy.h"
#include "list.h"
#include "colors.h"
#include "player.h"
#include "map.h"
#include "main.h"
#include "gui.h"

static enemy_template_t rulebook[100];
int book_length = 0;
int called = 0;

int hag = 0;
int fake_hag = 0;
int snek = 0;

void generate_enemies()
{
    called = 1;

    /* rat */
    rulebook[book_length].name = "rat";
    rulebook[book_length].pic = 'r' | A_BOLD | COLORS_RED;
    rulebook[book_length].base_hp = 30;
    rulebook[book_length].base_sight_range = 10;
    rulebook[book_length].base_exp = 10;
    rulebook[book_length].base_speed = 5;
    rulebook[book_length].base_strength = 5;
    rulebook[book_length].stat_int = 5;
    rulebook[book_length].stat_dex = 5;
    rulebook[book_length].stat_str = 5;
    book_length++;

    /* kobold */
    rulebook[book_length].name = "kobold";
    rulebook[book_length].pic = 'k' | A_BOLD | COLORS_RED;
    rulebook[book_length].base_hp = 50;
    rulebook[book_length].base_sight_range = 15;
    rulebook[book_length].base_strength = 10;
    rulebook[book_length].base_speed = 5;
    rulebook[book_length].base_exp = 15;
    rulebook[book_length].stat_int = 0;
    rulebook[book_length].stat_dex = 5;
    rulebook[book_length].stat_str = 5;
    book_length++;

    /* goblin */
    rulebook[book_length].name = "goblin";
    rulebook[book_length].pic = 'g' | A_BOLD | COLORS_RED;
    rulebook[book_length].base_hp = 50;
    rulebook[book_length].base_sight_range = 15;
    rulebook[book_length].base_strength = 15;
    rulebook[book_length].base_speed = 6;
    rulebook[book_length].base_exp = 15;
    rulebook[book_length].stat_int = 5;
    rulebook[book_length].stat_dex = 0;
    rulebook[book_length].stat_str = 5;
    book_length++;

    /* snake */
    rulebook[book_length].name = "snek";
    rulebook[book_length].pic = 's' | A_BOLD | COLORS_RED;
    rulebook[book_length].base_hp = 50;
    rulebook[book_length].base_sight_range = 15;
    rulebook[book_length].base_strength = 15;
    rulebook[book_length].base_speed = 5;
    rulebook[book_length].base_exp = 15;
    rulebook[book_length].stat_int = 5;
    rulebook[book_length].stat_dex = 5;
    rulebook[book_length].stat_str = 0;
    snek = book_length;
    book_length++;

    /* slime */
    rulebook[book_length].name = "slime";
    rulebook[book_length].pic = 'm' | A_BOLD | COLORS_RED;
    rulebook[book_length].base_hp = 75;
    rulebook[book_length].base_sight_range = 15;
    rulebook[book_length].base_strength = 7;
    rulebook[book_length].base_speed = 5;
    rulebook[book_length].base_exp = 20;
    rulebook[book_length].stat_int = 5;
    rulebook[book_length].stat_dex = 5;
    rulebook[book_length].stat_str = 10;
    book_length++;

    /* orc */
    rulebook[book_length].name = "orc";
    rulebook[book_length].pic = 'o' | A_BOLD | COLORS_RED;
    rulebook[book_length].base_hp = 75;
    rulebook[book_length].base_sight_range = 15;
    rulebook[book_length].base_strength = 15;
    rulebook[book_length].base_speed = 5;
    rulebook[book_length].base_exp = 20;
    rulebook[book_length].stat_int = 5;
    rulebook[book_length].stat_dex = 5;
    rulebook[book_length].stat_str = 5;
    book_length++;

    /* wolf */
    rulebook[book_length].name = "wolf";
    rulebook[book_length].pic = 'w' | A_BOLD | COLORS_RED;
    rulebook[book_length].base_hp = 50;
    rulebook[book_length].base_sight_range = 15;
    rulebook[book_length].base_strength = 30;
    rulebook[book_length].base_speed = 5;
    rulebook[book_length].base_exp = 30;
    rulebook[book_length].stat_int = 5;
    rulebook[book_length].stat_dex = 5;
    rulebook[book_length].stat_str = 5;
    book_length++;

    /* imp */
    rulebook[book_length].name = "imp";
    rulebook[book_length].pic = 'i' | A_BOLD | COLORS_RED;
    rulebook[book_length].base_hp = 75;
    rulebook[book_length].base_sight_range = 15;
    rulebook[book_length].base_strength = 30;
    rulebook[book_length].base_speed = 5;
    rulebook[book_length].base_exp = 35;
    rulebook[book_length].stat_int = 10;
    rulebook[book_length].stat_dex = 5;
    rulebook[book_length].stat_str = 5;
    book_length++;

    /* griffin */
    rulebook[book_length].name = "griffin";
    rulebook[book_length].pic = 'G' | A_BOLD | COLORS_RED;
    rulebook[book_length].base_hp = 100;
    rulebook[book_length].base_sight_range = 20;
    rulebook[book_length].base_strength = 30;
    rulebook[book_length].base_speed = 5;
    rulebook[book_length].base_exp = 40;
    rulebook[book_length].stat_int = 5;
    rulebook[book_length].stat_dex = 5;
    rulebook[book_length].stat_str = 5;
    book_length++;

    /* grue */
    rulebook[book_length].name = "grue";
    rulebook[book_length].pic = 'U' | A_BOLD | COLORS_RED;
    rulebook[book_length].base_hp = 60;
    rulebook[book_length].base_sight_range = 20;
    rulebook[book_length].base_strength = 50;
    rulebook[book_length].base_speed = 5;
    rulebook[book_length].base_exp = 40;
    rulebook[book_length].stat_int = 5;
    rulebook[book_length].stat_dex = 10;
    rulebook[book_length].stat_str = 5;
    book_length++;

    /* fake hag */
    rulebook[book_length].name = "Hag";
    rulebook[book_length].pic = 'H' | A_BOLD | COLORS_RED;
    rulebook[book_length].base_hp = 1;
    rulebook[book_length].base_sight_range = 0;
    rulebook[book_length].base_strength = 50;
    rulebook[book_length].base_speed = 5;
    rulebook[book_length].base_exp = 50;
    rulebook[book_length].stat_int = 5;
    rulebook[book_length].stat_dex = 5;
    rulebook[book_length].stat_str = 5;
    fake_hag = book_length;
    book_length++;

    /* hag */
    rulebook[book_length].name = "Hag";
    rulebook[book_length].pic = 'H' | A_BOLD | COLORS_RED;
    rulebook[book_length].base_hp = 30;
    rulebook[book_length].base_sight_range = 0;
    rulebook[book_length].base_strength = 60;
    rulebook[book_length].base_speed = 5;
    rulebook[book_length].base_exp = 70;
    rulebook[book_length].stat_int = 5;
    rulebook[book_length].stat_dex = 5;
    rulebook[book_length].stat_str = 5;
    hag = book_length;
    book_length++;
}

enemy_template_t *get_rulebook()
{
    if (!called) {
        generate_enemies();
    }
    return rulebook;
}

int enemy_index_hag()
{
    return hag;
}

int enemy_index_fake_hag()
{
    return fake_hag;
}


int enemy_index_snek()
{
    return snek;
}


void enemy_take_turn(enemy_t * e, WINDOW * win, int y, int x)
{
    enemy_t *n;
    enemy_template_t en;
    char msg[80];
    int w;
    int h;
    int y0;
    int x0;
    int i;
    int j;
    int ey;
    int ex;
    int yn = e->y;
    int xn = e->x;
    int ydiff = e->y - y;
    int xdiff = e->x - x;

    getmaxyx(win, h, w);        /*MACRO, changes w and h */
    y0 = y - (h / 2);
    x0 = x - (w / 2);

    ey = e->y - y0;
    ex = e->x - x0;

    if (ey >= 0 && ex >= 0 && ey < h && ex < w) {   /* if the enemy is on screen */
        /* TODO attacking */
        for (i = e->x - 1; i <= e->x + 1; i++) {
            for (j = e->y - 1; j <= e->y + 1; j++) {
                if (i == get_player_x() && j == get_player_y()) {
                    int damage = rand() % e->strength;
                    player_hurt(damage);
                    sprintf(msg, "The %s hurts you for %d life.",
                            rulebook[e->type].name, damage);
                    add_action(msg);
                    return;
                }
            }
        }

        if ((e->pic & A_CHARTEXT) == 'H') {
            if (tick % 24 == 0) {
                en = get_rulebook()[snek];
                add_action("The old hag summons a dangerous snek!");
                n = enemy_add(0, snek, en.pic, en.base_hp, e->y,
                              e->x + xdiff, en.base_sight_range,
                              en.base_strength, en.stat_str,
                              en.stat_dex, en.stat_int, en.base_speed,
                              en.base_exp, "dangerous snek");
                map_line(e->y, e->x, n->y, n->x);
            }
        }

        /* movement */
        /* if enemy is in range of the player */
        if (abs(ydiff) < e->sight_range && abs(xdiff) < e->sight_range) {
            if (xdiff < 0) {
                xn++;
            } else if (xdiff > 0) {
                xn--;
            }
            if (ydiff < 0) {
                yn++;
            } else if (ydiff > 0) {
                yn--;
            }
            if (map_get(yn, xn) == '.' && !enemy_at(yn, xn)) {
                e->y = yn;
                e->x = xn;
            } else if (map_get(yn, e->x) == '.' && !enemy_at(yn, e->x)) {
                e->y = yn;
            } else if (map_get(e->y, xn) == '.' && !enemy_at(e->y, xn)) {
                e->x = xn;
            }
        }
    }
}
