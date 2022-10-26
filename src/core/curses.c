#include <ncurses.h>
#include <curses.h>
#include <panel.h>
#include <sys/ioctl.h>
#include "gui.h"
#include "player.h"
#include "floor.h"
#include "enemy.h"
#include "item.h"
#include "colors.h"
#include "key.h"

static int h0;
static int w0;
static WINDOW *my_wins[3];
static PANEL *my_panels[3];

void curses_init(void)
{
    struct winsize w;
    int numRows;
    /*assuming character size is 15 by 15 pixels */
    /* getting the size of the terminal */
    /* https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c */
    ioctl(0, TIOCGWINSZ, &w);



    /* Initialize curses */
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    colors_init();

    init_wins(my_wins, w);

    /* Attach a panel to each window *//* Order is bottom up */
    my_panels[0] = new_panel(my_wins[0]);   /* Push 0, order: stdscr-0 */
    my_panels[1] = new_panel(my_wins[1]);   /* Push 1, order: stdscr-0-1 */
    my_panels[2] = new_panel(my_wins[2]);   /* Push 2, order: stdscr-0-1-2 */

    /* Set up the user pointers to the next panel */
    set_panel_userptr(my_panels[0], my_panels[1]);
    set_panel_userptr(my_panels[1], my_panels[2]);
    set_panel_userptr(my_panels[2], my_panels[0]);

    /*actions strings declaration */
    numRows = w.ws_row * .25 - 2;
    initialize_actions(numRows, my_wins[1]);

    /*ALL TEXT MUST BE PLACED BEFORE THE PANEL UPDATE */
    update_panels();

    /* Show it on the screen */
    attron(COLOR_PAIR(4));
    attroff(COLOR_PAIR(4));
    doupdate();
    gui_set_prompt_window(my_wins[1]);
}

void curses_update(void)
{
    player_t *player = get_player_obj();
    refresh();
    werase(my_wins[2]);
    print_stats(player, my_wins[2], floor_tick_get());
    key_checker(my_wins[2], player->y, player->x);
    update_panels();
    print_action();
    werase(my_wins[0]);
    map_print(my_wins[0], player->y, player->x);
    enemy_draw(my_wins[0], player->y, player->x);
    item_draw(my_wins[0], player->y, player->x);
    getmaxyx(my_wins[0], h0, w0);   /*MACRO, changes w and h */
    mvwprintw(my_wins[0], h0 / 2, w0 / 2, "@");
    wrefresh(my_wins[0]);
}
void curses_update_enemy(void)
{
    player_t *player = get_player_obj();
    enemy_turn_driver(my_wins[0], player->y, player->x);
    key_checker(my_wins[2], player->y, player->x);
}
void curses_update_end(void)
{
    player_t *player = get_player_obj();
    print_stats(player, my_wins[2], floor_tick_get());
    mvwprintw(my_wins[0], h0 / 2, w0 / 2, "t");
}
int curses_getch(void)
{
    return getch();
}
