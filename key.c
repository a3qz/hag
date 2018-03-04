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

static int inited = 0;
static list_t * key_list;

void key_setup(){
	if(!inited){
		inited = 1;
		key_list = list_create();
	}
}

void key_add_stair(int dir, int pic){
	system("echo crap > hello");
	key_setup();
	key_item_t *e = (key_item_t*)malloc(sizeof(*e));
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

	int starting_number = 10;
	int width = map_width();
	int height = map_height();
 	 int w, h;
     getmaxyx(win, h, w); //MACRO, changes w and h
	 int y0 = y - (h/2);
        int x0 = x - (w/2);
        int x1 = x + (w/2);
        int i = 0;
        int j = 0;
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
		char str[100];
		//fprintf(stderr, "x %d y %d h %d w %d i %d j %d \n",floor_up_xcoord(), floor_up_ycoord(),y0, x0, i, j);

		if (floor_up_xcoord() > i+x0 && floor_up_xcoord() < w+x0){
			if(floor_up_ycoord() > j+y0 && floor_up_ycoord() < h+y0){
				sprintf(str, " : %s, %s%d\n", "stairs up", "goto floor ", floor_get()-1);
				print_in_window(win, starting_number, 1, y, str, 0, false);
				mvwaddch(win, starting_number, 1, ('<' | A_BOLD | COLORS_BLUE));
				starting_number++;
			}else{
				print_in_window(win, starting_number, 1, y, "                                          ", 0, false);
				//exit(1);
			}
		} else{
						print_in_window(win, starting_number, 1, y, "                                          ", 0, false);

			//exit(2);
		}
        if (floor_down_xcoord() > i+x0 && floor_down_xcoord() < w+x0){
			if(floor_down_ycoord() > j+y0 && floor_down_ycoord() < h+y0){
				sprintf(str, " : %s, %s%d\n", "stairs down", "goto floor ", floor_get()+1);
				print_in_window(win, starting_number, 1, y, str, 0, false);
				mvwaddch(win, starting_number, 1, ('>' | A_BOLD | COLORS_BLUE));
			}else{
				print_in_window(win, starting_number, 1, y, "                                          ", 0, false);
				//exit(1);
			}
		} else{
						print_in_window(win, starting_number, 1, y, "                                          ", 0, false);

			//exit(2);
		}
 }