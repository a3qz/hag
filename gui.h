#ifndef GUI_H
#define GUI_H
	#include <ncurses.h>
	#include <panel.h>
	#include <string.h>
	#include <sys/ioctl.h>
	#include <stdio.h>
	#include <unistd.h>
	#include "player.h"

	void init_wins(WINDOW **wins, struct winsize w);
	void win_show(WINDOW *win, char *label, int label_color);
	void print_in_window(WINDOW *win, int starty, int startx, int width, char *string, chtype color, bool mid);
	void print_stats(WINDOW *win, struct player *p);
	void print_action(WINDOW *win);
	void add_action(char * s);
	void initialize_actions(int n);
#endif
