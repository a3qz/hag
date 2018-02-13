#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

char* map = "\
                                  ++++++++++++++++\
                                  +              +\
                                  +              +\
                                  +              +\
                                  +              +\
                                  +              +\
                                  +              +\
                                  +              +\
                                  +              +\
                                  +              +\
                                  +     ++++     +\
                                  +     +        +\
                                  ++++++++++++++++";
int main(int argc, char *argv[]) {
 int x = 40, y = 4;
 int max_y = 0, max_x = 0;
 int direction = 1;

 initscr();
 noecho();
 curs_set(0);

 // Global var `stdscr` is created by the call to `initscr()`
 getmaxyx(stdscr, max_y, max_x);

 while(1) {
//if (xp != x || yp != y) {
//    mvprintw(yp, xp, " ");
// }
 clear();
 int i;
 for (i = 0; i < 13; i++) {
     mvaddnstr(i, 0, map+i*50, 50);
 }
 mvprintw(y, x, "o");
 refresh();
 usleep(DELAY);
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
 if ((mvinch(yn, xn) & A_CHARTEXT) == ' ') {
    x = xn;
    y = yn;
 } 
 }

 endwin();
}
