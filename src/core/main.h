#ifndef MAIN_H
#include "player.h"
extern int tick;
void player_attacks(player_t *player, enemy_t *at);
int is_halloween(void);
void set_halloween(int h);
#endif
