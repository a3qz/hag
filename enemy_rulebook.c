#include "enemy_rulebook.h"
#include "list.h"
#include "colors.h"

static enemy_template_t rulebook[100];
int book_length = 0;
int called = 0;

void generate_enemies(){
	called = 1;

	// rat
	rulebook[book_length].name = "rat";
	rulebook[book_length].pic = 'r'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 30;
	rulebook[book_length].base_sight_range = 10;
	rulebook[book_length].base_strength = 5;
	book_length++;

	// kobold
	rulebook[book_length].name = "kobold";
	rulebook[book_length].pic = 'k'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 50;
	rulebook[book_length].base_sight_range = 15;
	rulebook[book_length].base_strength = 10;
	rulebook[book_length].base_exp = 10;
	book_length++;

	// goblin
	rulebook[book_length].name = "goblin";
	rulebook[book_length].pic = 'g'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 50;
	rulebook[book_length].base_sight_range = 15;
	rulebook[book_length].base_strength = 15;
	rulebook[book_length].base_exp = 15;
	book_length++;

	// snake
	rulebook[book_length].name = "snek";
	rulebook[book_length].pic = 's'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 50;
	rulebook[book_length].base_sight_range = 15;
	rulebook[book_length].base_strength = 15;
	rulebook[book_length].base_exp = 15;
	book_length++;

	// slime
	rulebook[book_length].name = "slime";
	rulebook[book_length].pic = 'm'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 75;
	rulebook[book_length].base_sight_range = 15;
	rulebook[book_length].base_strength = 7;
	rulebook[book_length].base_exp = 20;
	book_length++;

	// orc
	rulebook[book_length].name = "orc";
	rulebook[book_length].pic = 'o'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 75;
	rulebook[book_length].base_sight_range = 15;
	rulebook[book_length].base_strength = 15;
	rulebook[book_length].base_exp = 20;
	book_length++;

	// wolf
	rulebook[book_length].name = "wolf";
	rulebook[book_length].pic = 'w'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 50;
	rulebook[book_length].base_sight_range = 15;
	rulebook[book_length].base_strength = 30;
	rulebook[book_length].base_exp = 30;
	book_length++;

	// imp
	rulebook[book_length].name = "imp";
	rulebook[book_length].pic = 'i'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 75;
	rulebook[book_length].base_sight_range = 15;
	rulebook[book_length].base_strength = 30;
	rulebook[book_length].base_exp = 35;
	book_length++;

	// griffin
	rulebook[book_length].name = "griffin";
	rulebook[book_length].pic = 'G'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 100;
	rulebook[book_length].base_sight_range = 20;
	rulebook[book_length].base_strength = 30;
	rulebook[book_length].base_exp = 40;
	book_length++;

	// grue
	rulebook[book_length].name = "grue";
	rulebook[book_length].pic = 'U'|A_BOLD| COLORS_RED;
	rulebook[book_length].base_hp = 60;
	rulebook[book_length].base_sight_range = 20;
	rulebook[book_length].base_strength = 50;
	rulebook[book_length].base_exp = 40;
	book_length++;
	

}
enemy_template_t * get_rulebook(){
	if(!called){
		generate_enemies();
	}
	return rulebook;
}
