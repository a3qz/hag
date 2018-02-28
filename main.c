#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "map.h"
#include "floor.h"
#include "list.h"
#include "enemy.h"

#define W 60
#define H 13

//#define NLINES 60
//#define NCOLS 60

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

void init_wins(WINDOW **wins);
void win_show(WINDOW *win, char *label, int label_color);
void print_in_window(WINDOW *win, int starty, int startx, int width, char *string, chtype color, bool mid);

int main()
{
	WINDOW *my_wins[3];
	PANEL  *my_panels[3];
	PANEL  *top;
	int ch;

    floor_down();
	
	/* Initialize curses */
	initscr();
	start_color();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);

	/* Initialize all the colors */
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);

	init_wins(my_wins);
	
	/* Attach a panel to each window */ 	/* Order is bottom up */
	my_panels[0] = new_panel(my_wins[0]); 	/* Push 0, order: stdscr-0 */
	my_panels[1] = new_panel(my_wins[1]); 	/* Push 1, order: stdscr-0-1 */
	my_panels[2] = new_panel(my_wins[2]); 	/* Push 2, order: stdscr-0-1-2 */

	/* Set up the user pointers to the next panel */
	set_panel_userptr(my_panels[0], my_panels[1]);
	set_panel_userptr(my_panels[1], my_panels[2]);
	set_panel_userptr(my_panels[2], my_panels[0]);

	/* Update the stacking order. 2nd panel will be on top */
	update_panels();

	/* Show it on the screen */
	attron(COLOR_PAIR(4));
	mvprintw(LINES - 2, 0, "Use tab to browse through the windows (F1 to Exit)");
	attroff(COLOR_PAIR(4));
	doupdate();

    int x = 50, y = 50;
    int max_y = 0, max_x = 0;

    enemy_add(0, 'X', 5, 9, 51, 15);
    enemy_add(0, 'X', 5, 2, 49, 15);
    enemy_add(0, 'X', 5, x+2, y+2, 15);

    while(1) {
        refresh();
        wclear(my_wins[0]);
        map_print(my_wins[0], y, x);
        enemy_draw(my_wins[0], y, x);
        int w0, h0;
        getmaxyx(my_wins[0], h0, w0); //MACRO, changes w and h
        mvwprintw(my_wins[0], h0/2, w0/2, "@");
        wrefresh(my_wins[0]);
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
				case 'b':
					xn--;
					yn++;
					break;
				case 'n':
					xn++;
					yn++;
					break;	
				case 'y':
					xn--;
					yn--;
					break;	
				case 'u':
					xn++;
					yn--;
					break;
            }
        }
        enemy_t *at = enemy_at(yn, xn);
        if (map_get(yn, xn) == '.') {
            if (at) {
                enemy_hurt(at, 1);
            } else {
                x = xn;
                y = yn;
            }
        } 
		enemy_turn_driver(my_wins[0], y, x);

    }

    /*
	//top = my_panels[2];
	while((ch = getch()) != KEY_F(1))
	{
		char printer[100];
		sprintf(printer, "%c", ch);
		int y, x, NCOLS, NLINES;
		getyx(my_wins[1], y, x);
		getbegyx(my_wins[1], NCOLS, NLINES);
		
		print_in_window(my_wins[1], y, x, NCOLS, printer, 1, false);	
		wrefresh(my_wins[1]);
		if (ch == 13) {
			scrollok(my_wins[1], TRUE);
		}
		
		update_panels();
		doupdate();
	}
    */
	endwin();
	return 0;
}

/* Put all the windows */
void init_wins(WINDOW **wins) //int n)
{	

	//assuming character size is 15 by 15 pixels
	// getting the size of the terminal
	// https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
	struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);

	int x, y, i, width, height;
	char label[80];

	//HEIGHT WIDTH Y X (order of inputs for newwin)
	//storing the height and width of the terminal
	int NLINES = w.ws_row;
	int NCOLS = w.ws_col;

	//top left	
	wins[0] = newwin(NLINES*.75, NCOLS/2, 0, 0);
	sprintf(label, "Window Number %d", 1);
	win_show(wins[0], label, 1);
	
	//bottom 
	wins[1] = newwin(NLINES*.25, NCOLS, NLINES*.75, 0);
	sprintf(label, "%i %i", (int)(NLINES*.75)*15, 0);
	win_show(wins[1], label, 2);
	
	//top right
	wins[2] = newwin(NLINES*.75, NCOLS/2, 0, NCOLS*.5);
	sprintf(label, "%i %f", 0, ((int)NCOLS*.5*15));
	win_show(wins[2], label, 3);
}

/* Show the window with a border and a label */
void win_show(WINDOW *win, char *label, int label_color)
{	int startx, starty, height, width;

	getbegyx(win, starty, startx);
	getmaxyx(win, height, width);

	box(win, 0, 0);
	mvwaddch(win, 2, 0, ACS_LTEE); 
	mvwhline(win, 2, 1, ACS_HLINE, width - 2); 
	mvwaddch(win, 2, width - 1, ACS_RTEE); 
	
	print_in_window(win, 1, 0, width, label, COLOR_PAIR(label_color), true);
	print_in_window(win, 6, 0, width, "HELLO", COLOR_PAIR(label_color), false);
}

void print_in_window(WINDOW *win, int starty, int startx, int width, char *string, chtype color, bool mid)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	if (mid) {
		temp = (width - length)/ 2;
	} else {
		temp = 0;
		startx = 1;
	}
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}
