#include <ncurses.h>
#include <panel.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#include "args.h"
#include "player.h"
#include "colors.h"
#include "controls.h"
#include "map.h"
#include "item.h"
#include "flavortext.h"
#include "floor.h"
#include "list.h"
#include "enemy_rulebook.h"
#include "enemy.h"
#include "gui.h"
#include "key.h"

#define W 60
#define H 13

int tick = 0;

int main(int argc, char **argv)
{
    int repeat_act = 0;
    int fight_pre = 0;
    int run_pre = 0;
    int w0;
    int h0;
    int xn;
    int yn;
    int xp;
    int yp;
    int ch;
    int moved;
    int numRows;
    struct winsize w;
    item_t *item;
    player_t *player;
    enemy_t *at;
    WINDOW *my_wins[3];
    PANEL *my_panels[3];
    parse_args(argc, argv);

    /*assuming character size is 15 by 15 pixels */
    /* getting the size of the terminal */
    /* https://stackoverflow.com/questions/1022957/getting-terminal-width-in-c */
    ioctl(0, TIOCGWINSZ, &w);


    floor_down();
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

    player = get_player_obj();
    gui_set_prompt_window(my_wins[1]);
    item_give();
    add_action(flavortext_from_floor());
    map_los(player->y, player->x, 8, '.' | A_BOLD | COLORS_WHITE);
    xp = player->x;
    yp = player->y;

    while (player->current_hp > 0) {
        moved = 1;
        map_los(yp, xp, 8, (int)'.' | COLORS_BLACK | A_BOLD);
        map_los(player->y, player->x, 8, '.' | A_BOLD | COLORS_WHITE);
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
        xn = xp = player->x;
        yn = yp = player->y;
        ch = ERR;
        if ((ch = repeat_act) || (ch = getch(), ch != ERR)) {
            if (rand() % player->luck) {
                switch (ch) {
                case KEY_FIGHT:
                    moved = 0;
                    fight_pre = 1;
                    break;
                case KEY_RUN_N:
                case KEY_RUN_S:
                case KEY_RUN_E:
                case KEY_RUN_W:
                case KEY_RUN_NE:
                case KEY_RUN_NW:
                case KEY_RUN_SE:
                case KEY_RUN_SW:
                    moved = 0;
                    run_pre = 1;
                    repeat_act = tolower(ch);
                    break;
                case KEY_MOVE_N_BABBY:
                    add_action("Hey babby use j");
                /* fallthrough */
                case KEY_MOVE_N:
                    yn++;
                    break;
                case KEY_MOVE_S_BABBY:
                    add_action("Hey babby use k");
                /* fallthrough */
                case KEY_MOVE_S:
                    yn--;
                    break;
                case KEY_MOVE_W_BABBY:
                    add_action("Hey babby use h");
                /* fallthrough */
                case KEY_MOVE_W:
                    xn--;
                    break;
                case KEY_MOVE_E_BABBY:
                    add_action("Hey babby use l");
                /* fallthrough */
                case KEY_MOVE_E:
                    xn++;
                    break;
                case KEY_MOVE_NW:
                    xn--;
                    yn++;
                    break;
                case KEY_MOVE_NE:
                    xn++;
                    yn++;
                    break;
                case KEY_MOVE_SW:
                    xn--;
                    yn--;
                    break;
                case KEY_MOVE_SE:
                    xn++;
                    yn--;
                    break;
                case KEY_CLIMB_DOWN:
                    if (map_get(player->y, player->x) == '>') {
                        add_action("You climb down the ladder.");
                        floor_down();
                        add_action(flavortext_from_floor());
                        continue;
                    }
                    break;
                case KEY_CLIMB_UP:
                    if (map_get(player->y, player->x) == '<') {
                        add_action("You climb up the ladder.");
                        floor_up();
                        continue;
                    }
                    break;
                case KEY_QWARF:
                    item = item_at(player->y, player->x);
                    if (item && item->type == POTION) {
                        item_drink(item);
                    }
                    break;
                case KEY_INSPECT:
                    item = item_at(player->y, player->x);
                    if (item && item->type == POTION) {
                        item_inspect(item);
                    }
                    break;
                case KEY_EQUIP:
                    item = item_at(player->y, player->x);
                    if (item && item->type == SWORD) {
                        add_action("Picked up a sword");
                        item_swap(item);
                    }
                    break;
                case KEY_BIDE:
                    break;
                case KEY_QUIT:
                    endwin();
                    return 0;
                    break;
                case KEY_QUESTIONMARK:
                    add_action("Babby Manual:");
                    add_action("    h|j|k|l -> Left, Down, Up, Right");
                    add_action
                        ("    y|u|b|n -> Up Left, Up Right, Down Left, Down Right");
                    add_action
                        ("    Combat: walk into the enemy you want to attack");
                    add_action("    e -> pickup/swap with item on ground");
                    add_action
                        ("    <|> -> go up an up staircase|down a down staircase");
                    add_action
                        ("    s|d|i -> increase strength|dexterity|intelligence on levelup");
                    add_action("    F4 -> quit the game");
                    break;
                default:
                    add_action("Invalid button. Press '?' for the manual");
                    moved = 0;
                    continue;
                    break;
                }
            } else {
                add_action("You tripped.");
                if (player->luck < 50) {
                    player->luck += 1;
                }
            }
            if (floor_tick() == 2) {
                add_action
                    ("You hear the hag cackling from somewhere deep inside the dungeon.");
                add_action
                    ("You feel like every step you take on this floor will hurt you.");
            }
        }
        at = enemy_at(yn, xn);
        if (map_get(yn, xn) == '.' || map_get(yn, xn) == '<'
            || map_get(yn, xn) == '>') {
            if (at) {
                if (fight_pre == 1) {
                    repeat_act = ch;
                    fight_pre = 2;
                }
                if (run_pre) {
                    run_pre = 0;
                    repeat_act = 0;
                }
                if (rand() % player->luck == 0) {
                    char msg[80];
                    sprintf(msg, "You swing at the %s, but miss.",
                            get_rulebook()[at->type].name);
                    add_action(msg);
                } else {
                    int damage = player_damage_dealt();
                    damage *= 10 - *(&at->stat_str + item_stat() - 1);
                    damage /= 5;
                    if (rand() % 20000 < player->luck) {
                        char msg[80];
                        sprintf(msg,
                                "You land a critical blow against the %s for %d life.",
                                get_rulebook()[at->type].name, damage * 2);
                        add_action(msg);
                        enemy_hurt(at, damage * 2);
                    } else {
                        char msg[80];
                        sprintf(msg, "You hurt the %s for %d life.",
                                get_rulebook()[at->type].name, damage);
                        add_action(msg);
                        enemy_hurt(at, damage);
                    }
                }
            } else {
                if (fight_pre == 2) {
                    repeat_act = 0;
                    fight_pre = 0;
                }
                player->x = xn;
                player->y = yn;
            }
        } else {
            if (run_pre) {
                run_pre = 0;
                repeat_act = 0;
            } else {
                add_action("You can't walk through walls.");
            }
        }
        enemy_turn_driver(my_wins[0], player->y, player->x);
        key_checker(my_wins[2], player->y, player->x);
        if (moved) {
            tick++;
        }
    }
    print_stats(player, my_wins[2], floor_tick_get());
    gui_prompt("You have died! Press space to exit.", " ");

    endwin();
    return 0;
}
