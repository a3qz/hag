#include <ncurses.h>
#include <stdio.h>
#include "floor.h"
#include "list.h"
#include "time.h"
#include "colors.h"
#include "item.h"
#include "enemy.h"
#include "enemy_rulebook.h"
#include "player.h"
#include "key.h"
#include "gui.h"

char * weapontypes[4] = {"", "Strength", "Dexterity", "Intelligence"};
static int inited = 0;
static list_t * key_list;

void key_setup(){
    if(!inited){
        inited = 1;
        key_list = list_create();
    }
}

void key_add_stair(int dir, int pic){
    key_item_t *e;
    system("echo crap > hello");
    key_setup();
    e = (key_item_t*)malloc(sizeof(*e));
    if(dir == 0){
        e->name = "stairs up";
    } else{
        e->name = "stairs down";
    }
    sprintf((e->extra_info), "goto floor %d", floor_get()-1);

    e->pic = pic;
    system("echo crap > hello");
    e->node = list_add_tail(key_list, e);

}

list_t* key_get_list(){
    return key_list;
}

void key_checker(WINDOW *win, int y, int x){
    int i = 0;
    int j = 0;
    int starting_number = 11;
    int width = map_width();
    int w;
    int h;
    int y0;
    int x0;
    int x1;
    char str[100];
    enemy_t *e;
    item_t *it;
    getmaxyx(win, h, w); /*MACRO, changes w and h */
    y0 = y - (h/2);
    x0 = x - (w/2);
    x1 = x + (w/2);
    if (y0 < 0) {
        i -= y0;
        y0 = 0;
    }
    if (x0 < 0) {
        j -= x0;
        w -= j;
        x0 = 0;
    }
    if (x1 > width) {
        w -= x1 - width;
    }
    if (floor_up_xcoord() > i+x0 && floor_up_xcoord() < w+x0){
        if(floor_up_ycoord() > j+y0 && floor_up_ycoord() < h+y0){
            sprintf(str, " : %s, %s%d\n", "stairs up", "goto floor ", floor_get()-1);
            print_in_window(win, starting_number, 1, y, str, 0, false);
            mvwaddch(win, starting_number, 1, ('<' | A_BOLD | COLORS_BLUE));
            starting_number++;
        }else{
            print_in_window(win, starting_number, 1, y, "                                          ", 0, false);
            /*exit(1); */
        }
    } else{
        print_in_window(win, starting_number, 1, y, "                                          ", 0, false);

        /*exit(2); */
    }
    if (floor_down_xcoord() > i+x0 && floor_down_xcoord() < w+x0){
        if(floor_down_ycoord() > j+y0 && floor_down_ycoord() < h+y0){
            sprintf(str, " : %s, %s%d\n", "stairs down", "goto floor ", floor_get()+1);
            print_in_window(win, starting_number, 1, y, str, 0, false);
            mvwaddch(win, starting_number, 1, ('>' | A_BOLD | COLORS_BLUE));
            starting_number++;
        }else{
            print_in_window(win, starting_number, 1, y, "                                          ", 0, false);
        }
    } else{
        print_in_window(win, starting_number, 1, y, "                                          ", 0, false);
    }

    list_traverse(get_enemy_list()->head);
    while ((e = list_traverse(0))) {
        if (e->x > i+x0 && e->x < w+x0){
            if(e->y > j+y0 && e->y < h+y0){
                sprintf(str, " : %s %s%d\n", get_rulebook()[e->type].name, "HP: ", e->hp);
                print_in_window(win, starting_number, 1, y, str, 0, false);
                mvwaddch(win, starting_number, 1, (e->pic));
                starting_number++;
            }else{
                print_in_window(win, starting_number, 1, y, "                                          ", 0, false);
            }
        } else{
            print_in_window(win, starting_number, 1, y, "                                          ", 0, false);
        }
    }
    list_traverse(get_item_list()->head);
    while ((it = list_traverse(0))) {
        if (it->x > i+x0 && it->x < w+x0){
            if(it->y > j+y0 && it->y < h+y0){
                if (it->type == SWORD) {    
                    sprintf(str, " : %s Weapon\n", weapontypes[it->stat]);
                    print_in_window(win, starting_number, 1, y, str, 0, false);
                    mvwaddch(win, starting_number, 1, (it->pic)?it->pic:' ' );
                    starting_number++;
                } else {
                    sprintf(str, " : Potion\n");
                    print_in_window(win, starting_number, 1, y, str, 0, false);
                    mvwaddch(win, starting_number, 1, (it->pic)?it->pic:' ' );
                    starting_number++;
                }
            }else{
                print_in_window(win, starting_number, 1, y, "                                          ", 0, false);
            }
        } else{
            print_in_window(win, starting_number, 1, y, "                                          ", 0, false);
        }
    }

    box(win, 0, 0);
}
