#ifndef ENEMY_RULEBOOK_H
#define ENEMY_RULEBOOK_H
#include <ncurses.h>
#include "enemy.h"
typedef struct enemy_template {
    char *name;
    int pic;
    int base_hp;
    int base_sight_range;
    int base_strength;
    int base_speed;
    int base_exp;
    int stat_int;
    int stat_dex;
    int stat_str;
} enemy_template_t;
void generate_enemies(void);
enemy_template_t *get_rulebook(void);
void enemy_take_turn(enemy_t * e, WINDOW * win, int player_y,
                     int player_x);
int enemy_index_hag(void);
int enemy_index_snek(void);
int enemy_index_fake_hag(void);
#endif
