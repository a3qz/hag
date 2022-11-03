#include <ncurses.h>
#include <curses.h>
#include <panel.h>
#include <string.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#include "demo.h"
#include "args.h"
#include "player.h"
#include "colors.h"
#include "curses.h"
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
#include "main.h"

#define W 60
#define H 13

int tick = 0;

int main(int argc, char **argv)
{
    int repeat_act = 0;
    int fight_pre = 0;
    int run_pre = 0;
    int xn;
    int yn;
    int xp;
    int yp;
    int ch;
    int moved;
    item_t *item;
    player_t *player;
    enemy_t *at;
    parse_args(argc, argv);
    curses_init();
    floor_down();
    player = get_player_obj();
    item_give();
    add_action(flavortext_from_floor());
    map_los(player->y, player->x, 8, '.' | A_BOLD | COLORS_WHITE);
    xp = player->x;
    yp = player->y;

    for (ch = 0; ch <= FLOOR_COUNT; ch++) {
        floor_goto(ch);
    }
    floor_goto(0);

    while (player->current_hp > 0) {
        moved = 1;
        map_los(yp, xp, 8, (int)'.' | COLORS_BLACK | A_BOLD);
        map_los(player->y, player->x, 8, '.' | A_BOLD | COLORS_WHITE);
        curses_update();
        xn = xp = player->x;
        yn = yp = player->y;
        if ((ch = repeat_act) || (ch = demo_next(), ch != ERR)) {
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
                case KEY_SCROLL_UP:
                    set_scroll(get_scroll() - 1);
                    continue;
                case KEY_SCROLL_DOWN:
                    set_scroll(get_scroll() + 1);
                    continue;
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
                    add_action("    [  -> scroll action log up");
                    add_action("    ]  -> scroll action log down");
                    break;
                default:
                    add_action("Invalid button. Press '?' for the manual");
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
                player_attacks(player, at);
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
        curses_update_enemy();
        if (moved) {
            tick++;
        }
    }
    curses_update_end();
    gui_prompt("You have died! Press space to exit.", " ");

    endwin();
    return 0;
}
void player_attacks(player_t *player, enemy_t *at)
{
    int damage;
    damage = player_damage_dealt();
    if ((rand() % player->luck == 0) || (damage == 0)) {
        char msg[80];
        sprintf(msg, "You swing at the %s, but miss.",
                get_rulebook()[at->type].name);
        add_action(msg);
    } else {
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
}
