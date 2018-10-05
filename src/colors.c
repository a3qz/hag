#include <ncurses.h>
#include "colors.h"

#define COLORS_PAIR_RED    1
#define COLORS_PAIR_GREEN  2
#define COLORS_PAIR_BLUE   3
#define COLORS_PAIR_CYAN   4
#define COLORS_PAIR_YELLOW 5
#define COLORS_PAIR_WHITE  6
#define COLORS_PAIR_GRAY   7

const int COLORS_RED    = COLOR_PAIR(COLORS_PAIR_RED);
const int COLORS_GREEN  = COLOR_PAIR(COLORS_PAIR_GREEN);
const int COLORS_BLUE   = COLOR_PAIR(COLORS_PAIR_BLUE);
const int COLORS_CYAN   = COLOR_PAIR(COLORS_PAIR_CYAN);
const int COLORS_YELLOW = COLOR_PAIR(COLORS_PAIR_YELLOW);
const int COLORS_WHITE  = COLOR_PAIR(COLORS_PAIR_WHITE);
const int COLORS_GRAY   = COLOR_PAIR(COLORS_PAIR_GRAY) | A_DIM;

void colors_init() {
	/* Initialize all the colors */
	start_color();

    init_color(COLOR_RED,     1000,    0,    0);
    init_color(COLOR_GREEN,      0, 1000,    0);
    init_color(COLOR_BLUE,       0,    0, 1000);
    init_color(COLOR_CYAN,       0,  500, 1000);
    init_color(COLOR_YELLOW,  1000, 1000,    0);
    init_color(COLOR_WHITE,   1000, 1000, 1000);
    init_color(9,   900, 900, 900);

	init_pair(COLORS_PAIR_RED,    COLOR_RED,    COLOR_BLACK);
	init_pair(COLORS_PAIR_GREEN,  COLOR_GREEN,  COLOR_BLACK);
	init_pair(COLORS_PAIR_BLUE,   COLOR_BLUE,   COLOR_BLACK);
	init_pair(COLORS_PAIR_CYAN,   COLOR_CYAN,   COLOR_BLACK);
	init_pair(COLORS_PAIR_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(COLORS_PAIR_WHITE,  COLOR_WHITE,  COLOR_BLACK);
	init_pair(COLORS_PAIR_GRAY,   COLOR_BLACK,  COLOR_BLACK);
}
