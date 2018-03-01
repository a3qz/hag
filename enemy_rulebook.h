#ifndef ENEMY_RULEBOOK_H
#define ENEMY_RULEBOOK_H
    #include <ncurses.h>
    typedef struct enemy_template {
		char * name;
        int pic;
        int base_hp;
        int base_sight_range;
        int base_strength;
    } enemy_template_t;
	void generate_enemies();
	enemy_template_t * get_rulebook();
#endif
