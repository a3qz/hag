#include "enemy_rulebook.h"
#include "list.h"
#include "colors.h"

static enemy_template_t rulebook[100];
int book_length = 0;

void generate_enemies(){
	rulebook[book_length].name = "kobold";
	rulebook[book_length].pic = 'k'|COLORS_RED;
	book_length++;
}
enemy_template_t * get_rulebook(){
	return rulebook;
}
