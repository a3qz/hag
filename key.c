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

		if (floor_up_xcoord() > i && floor_up_xcoord() < height){
			if(floor_up_ycoord() > j && floor_up_ycoord() < w){
				key_add_stair(0, ('<' | A_BOLD | COLORS_BLUE));
				system("echo asdfsadfasdf > hitest");
			}
		}
        /*for (; i < h && y0 < height; i++) {
            int k;
            for (k = 0; k < w && x0+k<width; k++) {
                mvwaddch(win, i, j + k, map[y0][x0+k]);
				if(map[y0][x0+k] == ('<' | A_BOLD | COLORS_BLUE)){
					
				} else if(map[y0][x0+k] == ('>' | A_BOLD | COLORS_BLUE)){
					key_add_stair(1, ('>' | A_BOLD | COLORS_BLUE));
				}
            }
            y0++;
        }*/
 }