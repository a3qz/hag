#include <ncurses.h>
#include <unistd.h>

#include "map.h"
#include "list.h"

#define W 60
#define H 13

char* map[] = {
"           +++++++++++++++++++++++++++++++++++++++++++++++++",
"           +................................+..............+",
"           +...............................................+",
"           +..+.............................+..............+",
"++++++++++++..+++++++++++++++++++++++++++++++..............+",
"+.............+                             +..............+",
"+..++++++++++++                             +..............+",
"+..+++++++                                  +..............+",
"+..++....+                                  +..............+",
"++..+....+                                  +..............+",
" +.......+                                  +.....++++.....+",
" +.......+                                  +.....+........+",
" +++++++++                                  ++++++++++++++++"};

int main(int argc, char *argv[]) {
    
    int x = 50, y = 4;
    int max_y = 0, max_x = 0;

    initscr();
    noecho();
    curs_set(0);
    WINDOW *my_win = newwin(10, 10, 20, 20);
    map_load(map, W, H);

    while(1) {
        refresh();
        wclear(my_win);
        map_print(my_win, y, x);
        mvwprintw(my_win, 5, 5, "o");
        wrefresh(my_win);
        int xn = x, yn = y;
        int ch = ERR;
        if (ch = getch(), ch != ERR) {
            switch (ch) {
                case 'j':
                    yn++;
                    break;
                case 'k':
                    yn--;
                    break;
                case 'h':
                    xn--;
                    break;
                case 'l':
                    xn++;
                    break;
            }
        }
        if (map_get(yn, xn) == '.') {
            x = xn;
            y = yn;
        } 
    }

    endwin();
}
