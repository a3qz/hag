#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "gui.h"
#include "player.h"
#include "item.h"
#include "list.h"
#include "key.h"

#define ACTION_LENGTH 120

int junk;
int nelems;
char * statslist = " sdi";
WINDOW * prompt_window = 0;

char **actions;
char * str;
WINDOW * win;

void add_action(char * s){	
	int i;
	for (i = 1; i < nelems; i++){
		memset(actions[i-1], '\0', ACTION_LENGTH);
		strcpy(actions[i-1], actions[i]);

	}
	strcpy(actions[nelems - 1], s);
	werase(win);
	print_action();
}

void initialize_actions(int n, WINDOW * w){
	nelems = n;
	int i;
	win = w;
	actions = (char**)malloc(n*sizeof(char*));
	for (i = 0; i < nelems; i++){
		actions[i] = (char*)malloc(ACTION_LENGTH*sizeof(char));
		memset(actions[i], '\0', ACTION_LENGTH);
	}
}


/* Put all the windows */
void init_wins(WINDOW **wins, struct winsize w) /*int n) */
{	
	char label[80];

	/*HEIGHT WIDTH Y X (order of inputs for newwin) */
	/*storing the height and width of the terminal */
	int NLINES = w.ws_row;
	int NCOLS = w.ws_col;

	/*top left	 */
	wins[0] = newwin(NLINES*.75, NCOLS/2, 0, 0);
	sprintf(label, "Window Number %d", 1);
	win_show(wins[0], label, 1);
	
	/*bottom  */
	wins[1] = newwin(NLINES*.25, NCOLS, NLINES*.75, 0);
	sprintf(label, "%i %i", (int)(NLINES*.75)*15, 0);
	win_show(wins[1], label, 2);
	
	/*top right */
	wins[2] = newwin(NLINES*.75, NCOLS/2, 0, NCOLS*.5);
	sprintf(label, "%i %f", 0, ((int)NCOLS*.5*15));
	win_show(wins[2], label, 3);
}

/* Show the window with a border and a label */
void win_show(WINDOW *win, char *label, int label_color)
{
    int width;
	getmaxyx(win, junk, width);

	box(win, 0, 0);
	mvwaddch(win, 2, 0, ACS_LTEE); 
	mvwaddch(win, 2, width - 1, ACS_RTEE); 
	
}

void print_stats(struct player *p, WINDOW * win2){
	int y;
	getmaxyx(win2, y, junk);
	char c[y];
	char * str = c ;
	sprintf(str, "Current HP: %d/%d\n", p->current_hp, p->max_hp);
	print_in_window(win2, 1, 1, y, str, 0, false);
	sprintf(str, "Strength: %d\n", p->strength);
	print_in_window(win2, 2, 1, y, str, 0, false);
	sprintf(str, "Dexterity: %d\n", p->dexterity);
	print_in_window(win2, 3, 1, y, str, 0, false);
	sprintf(str, "Intelligence: %d\n", p->intelligence);
	print_in_window(win2, 4, 1, y, str, 0, false);
	sprintf(str, "Luck: %d\n", p->luck);
	print_in_window(win2, 5, 1, y, str, 0, false);
	sprintf(str, "Experience: %d/%d\n", p->current_exp, p->max_exp);
	print_in_window(win2, 6, 1, y, str, 0, false);
	sprintf(str, "Current Level: %d\n", p->current_level);
	print_in_window(win2, 7, 1, y, str, 0, false);
	sprintf(str, "Current Item: %c %d\n", statslist[item_stat()], item_power());
	print_in_window(win2, 8, 1, y, str, 0, false);
	sprintf(str, "\n");
	print_in_window(win2, 9, 1, y, str, 0, false);
	sprintf(str, "Key:\n");
	print_in_window(win2, 10, 1, y, str, 0, false);
	box(win2, 0, 0);
}

void print_action(){
	int y;
	getmaxyx(win, y, junk);
	int i;
	for (i = 0; i < nelems; i++){ 
		print_in_window(win, i+1, 1, y, actions[i], 0, false);
	}
	box(win, 0, 0);
}

char gui_prompt(char * prompt, char * answer){	
    if (!prompt_window || !answer) {
        return 0;
    }
    char response = -1;
    while (strchr(answer, response) == NULL) {
        add_action(prompt);
		print_action(prompt_window);
		update_panels();
        refresh();
        response = getch();
    }
    return response;
}

void gui_set_prompt_window(WINDOW *win) {
    prompt_window = win;
}


void print_in_window(WINDOW *win, int starty, int startx, int width, char *string, chtype color, bool mid)
{	
  int length, x, y;
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
