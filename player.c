#include "player.h"
#include <stdlib.h>

static player_t player = {200, 200, 50, 50, 25, 25, 25, 0, 100, 1};
player_t * get_player_obj(){
    return &player;
}
int get_player_y(){
    return player.y;
}
int get_player_x(){
    return player.x;
}
void set_player_y(int y){
    player.y = y;
}
void set_player_x(int x){
    player.x = x;
}
void player_hurt(int enemy_strength){
    if(player.current_hp - enemy_strength > 0){
        player.current_hp = player.current_hp - enemy_strength;
    } else{
        player.current_hp = 0;
    }

}
void player_gain_exp(int xp){
	player.current_exp += xp;
	if (player.current_exp >= player.max_exp){
		player.current_exp -= player.max_exp;
		player_levelup();
	}
}

void player_levelup(){
	player.current_level++;
	player.max_hp += player.max_hp/4;
	player.current_hp = player.max_hp;
	// call prompt to increase stats here
}