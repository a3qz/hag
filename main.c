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
#include "enemy_rulebook.h"
#include "enemy.h"
#include "gui.h"
#include "key.h"

#define W 60
#define H 13

/*#define NLINES 60 */
/*#define NCOLS 60 */

#define KEY_F(n)        (KEY_F0+(n))

int tick = 0;

int main()
{
	/*assuming character size is 15 by 15 pixels */
	/* getting the size of the terminal */
	/* https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c */
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

	/*actions strings declaration */
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
		werase(my_wins[2]);
		print_stats(player, my_wins[2]);
        key_checker(my_wins[2], player->y, player->x);
		update_panels();
		print_action();
        werase(my_wins[0]);
        map_print(my_wins[0], player->y, player->x);
        enemy_draw(my_wins[0], player->y, player->x);
        item_draw(my_wins[0], player->y, player->x);
        int w0, h0;
        getmaxyx(my_wins[0], h0, w0); /*MACRO, changes w and h */
        mvwprintw(my_wins[0], h0/2, w0/2, "@");
        wrefresh(my_wins[0]);
        int xn = player->x, yn = player->y;
        int ch = ERR;
        item_t *item;
        if (ch = getch(), ch != ERR) {
            if (rand()%player->luck) {
                switch (ch) {
                    case 0x102:
                    add_action("Hey babby use j");
                    case 'j':
                        yn++;
                        break;
                    case 0x103:
                    add_action("Hey babby use k");
                    case 'k':
                        yn--;
                        break;
                    case 0x104:
                    add_action("Hey babby use h");
                    case 'h':
                        xn--;
                        break;
                    case 0x105:
                    add_action("Hey babby use l");
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
                        add_action("You lame cheater.");
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
                        player->max_hp = 3000;
                        player->current_hp = 3000;
                        player->max_exp = 9999999;
                        item_swap(item_add(0, 0, 0));
                        break;
                    case '>':
                        if (map_get(player->y, player->x) == '>') {
                            add_action("You climb down the ladder.");
                            floor_down();
                            continue;
                        }
                        break;
                    case '<':
                        if (map_get(player->y, player->x) == '<') {
                            add_action("You climb up the ladder.");
                            floor_up();
                            continue;
                        }
                        break;
                    case 'q':
                        item = item_at(player->y, player->x);
                        if (item && item->type == POTION) {
                            item_drink(item);
                        }
                        break;
                    case 'e':
                        item = item_at(player->y, player->x);
                        if (item && item->type == SWORD) {
                            add_action("Picked up a sword");
                            item_swap(item);
                        }
                        break;
                    case '.':
                        break;
                    case 't':
                        /*enemy_add(0, 0, 'X', 45, player->y+1, player->x+1, 15, 10); */
                        break;
                    case KEY_F(4):
                        endwin();
                        return 0;
                        break;
                }
            } else {
                add_action("You tripped.");
            }
        }
        enemy_t *at = enemy_at(yn, xn);
        if (map_get(yn, xn) == '.' || map_get(yn, xn) == '<' || map_get(yn, xn) == '>') {
            if (at) {
                if (rand()%player->luck == 0) {
                    char msg[80];
                    sprintf(msg, "You swing at the %s, but miss.", get_rulebook()[at->type].name);
                    add_action(msg);
                } else {
                    if (rand()%20000<player->luck) {
                        char msg[80];
                        sprintf(msg, "You land a critical blow against the %s for %d life.", get_rulebook()[at->type].name, player_damage_dealt()*2);
                        add_action(msg);
                        enemy_hurt(at, player_damage_dealt()*2);
                    } else {
                        char msg[80];
                        sprintf(msg, "You hurt the %s for %d life.", get_rulebook()[at->type].name, player_damage_dealt());
                        add_action(msg);
                        enemy_hurt(at, player_damage_dealt());
                    }
                }
            } else {
                player->x = xn;
                player->y = yn;
            }
        } else {
            add_action("You can't walk through walls.");
        } 
		enemy_turn_driver(my_wins[0], player->y, player->x);
				key_checker(my_wins[2], player->y, player->x);
    }
    print_stats(player, my_wins[2]);
    gui_prompt("You have died! Press space to exit.", " ");

	endwin();
	return 0;
}
