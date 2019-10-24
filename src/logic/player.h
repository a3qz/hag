#ifndef PLAYER_H
#define PLAYER_H
typedef struct player {
    int current_hp;
    int max_hp;
    int y;
    int x;
    int strength;
    int dexterity;
    int intelligence;
    int current_exp;
    int max_exp;
    int current_level;
    int luck;
    int potion_count;
} player_t;

player_t *get_player_obj(void);
int get_player_y(void);
int get_player_x(void);
void set_player_y(int y);
void set_player_x(int x);
void player_hurt(int enemy_strength);
void player_gain_exp(int xp);
void player_levelup(void);
int player_damage_dealt(void);
#endif
