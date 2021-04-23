#ifndef COLORS_H
#define COLORS_H
#ifdef __APPLE__
    #define NCURSES_PAIRS_T int
#endif
extern const NCURSES_PAIRS_T COLORS_BLACK;
extern const NCURSES_PAIRS_T COLORS_RED;
extern const NCURSES_PAIRS_T COLORS_GREEN;
extern const NCURSES_PAIRS_T COLORS_YELLOW;
extern const NCURSES_PAIRS_T COLORS_BLUE;
extern const NCURSES_PAIRS_T COLORS_MAGENTA;
extern const NCURSES_PAIRS_T COLORS_CYAN;
extern const NCURSES_PAIRS_T COLORS_WHITE;
void colors_init(void);
#endif
