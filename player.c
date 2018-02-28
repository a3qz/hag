#include "player.h"
#include <stdlib.h>

static player_t player = {100, 100, 50, 50, 25, 25, 25};
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
        exit(1);
    }

}