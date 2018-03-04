#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include "player.h"
#include "colors.h"
#include "map.h"
#include "item.h"
#include "floor.h"
#include "list.h"
#include "enemy.h"
#include "gui.h"

#define W 60
#define H 13

//#define NLINES 60
//#define NCOLS 60

int tick = 0;

int main()
{
	//assuming character size is 15 by 15 pixels
	// getting the size of the terminal
	// https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c
	struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);

	WINDOW *my_wins[3];
	PANEL  *my_panels[3];


    floor_down();
	
	/* Initialize curses */
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);

    colors_init();

	init_wins(my_wins, w);
	
	/* Attach a panel to each window */ 	/* Order is bottom up */
	my_panels[0] = new_panel(my_wins[0]); 	/* Push 0, order: stdscr-0 */
	my_panels[1] = new_panel(my_wins[1]); 	/* Push 1, order: stdscr-0-1 */
	my_panels[2] = new_panel(my_wins[2]); 	/* Push 2, order: stdscr-0-1-2 */

	/* Set up the user pointers to the next panel */
	set_panel_userptr(my_panels[0], my_panels[1]);
	set_panel_userptr(my_panels[1], my_panels[2]);
	set_panel_userptr(my_panels[2], my_panels[0]);

	//actions strings declaration
	int numRows = w.ws_row * .25 - 2;
	initialize_actions(numRows, my_wins[1]);
	add_action("actions window");

	/*ALL TEXT MUST BE PLACED BEFORE THE PANEL UPDATE*/
	update_panels();

	/* Show it on the screen */
	attron(COLOR_PAIR(4));
	attroff(COLOR_PAIR(4));
	doupdate();

	player_t * player = get_player_obj();
    gui_set_prompt_window(my_wins[1]);
    item_give();
    while(player->current_hp > 0) {
        tick++;
        refresh();
		print_stats(player, my_wins[2]);
		update_panels();
		print_action();
        werase(my_wins[0]);
        map_print(my_wins[0], player->y, player->x);
        enemy_draw(my_wins[0], player->y, player->x);
        item_draw(my_wins[0], player->y, player->x);
        int w0, h0;
        getmaxyx(my_wins[0], h0, w0); //MACRO, changes w and h
        mvwprintw(my_wins[0], h0/2, w0/2, "@");
        wrefresh(my_wins[0]);
        int xn = player->x, yn = player->y;
        int ch = ERR;
        item_t *item;
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
				case 'c':
                    floor_down();
                    floor_down();
                    floor_down();
                    floor_down();
                    floor_down();
                    floor_down();
                    floor_down();
                    floor_down();
                    floor_down();
                    floor_down();
					break;
				case '>':
                    if (map_get(player->y, player->x) == '>') {
                        floor_down();
                    }
					break;
				case '<':
                    if (map_get(player->y, player->x) == '<') {
                        floor_up();
                    }
					break;
				case 'e':
                    item = item_at(player->y, player->x);
                    if (item) {
                        if (item->power == 0) {
                            item->power = 100;
                        }
                        add_action("picked up a sword");
                        item_swap(item);
                    }
					break;
				case '.':
					break;
				case 't':
    				//enemy_add(0, 0, 'X', 45, player->y+1, player->x+1, 15, 10);
					break;
            }
        }
        enemy_t *at = enemy_at(yn, xn);
        if (map_get(yn, xn) == '.' || map_get(yn, xn) == '<' || map_get(yn, xn) == '>') {
            if (at) {
                enemy_hurt(at, player_damage_dealt());
            } else {
                player->x = xn;
                player->y = yn;
            }
        } 
		enemy_turn_driver(my_wins[0], player->y, player->x);
    }
    print_stats(player, my_wins[2]);
    gui_prompt("You have died! Press space to exit.", " ");

	endwin();
	return 0;
}
