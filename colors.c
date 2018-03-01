#include <ncurses.h>
#include "colors.h"

#define COLORS_PAIR_RED    1
#define COLORS_PAIR_GREEN  2
#define COLORS_PAIR_BLUE   3
#define COLORS_PAIR_CYAN   4
#define COLORS_PAIR_YELLOW 5
#define COLORS_PAIR_WHITE  6

const int COLORS_RED = COLORS_PAIR_RED<<8;
const int COLORS_GREEN = COLORS_PAIR_GREEN<<8;
const int COLORS_BLUE = COLORS_PAIR_BLUE<<8;
const int COLORS_CYAN = COLORS_PAIR_CYAN<<8;
const int COLORS_YELLOW = COLORS_PAIR_YELLOW<<8;
const int COLORS_WHITE = COLORS_PAIR_WHITE<<8;

void colors_init() {
	/* Initialize all the colors */
	start_color();
	init_pair(COLORS_PAIR_RED, COLOR_RED, COLOR_BLACK);
	init_pair(COLORS_PAIR_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLORS_PAIR_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(COLORS_PAIR_CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(COLORS_PAIR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
}
