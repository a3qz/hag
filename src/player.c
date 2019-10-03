#include "player.h"
#include <stdlib.h>
#include "gui.h"
#include "item.h"
        int current_hp;
        int max_hp;
        int y;
        int x;
        int strength;
        int dexterity;
        int intelligence;
		int current_exp;
		int max_exp;
		int current_level;
        int luck;

static player_t player = {
    current_hp:    175, 
    max_hp:        175, 
    y:             50,
    x:             50, 
    strength:      10, 
    dexterity:     10,
    intelligence:  10, 
    current_exp:   0,
    max_exp:       112, 
    current_level: 1,
    luck:          1000
};

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
        player.max_exp += player.max_exp/5;
        player_levelup();
    }
}

void player_levelup(){
    player.current_level++;
    player.max_hp += player.max_hp/4;
    player.current_hp = player.max_hp;
    char res = gui_prompt("What stat would you like to increase? (s)trength, (d)exterity, or (i)ntelligence?", "sdi");
    switch(res){
        case 's':
            player.strength += 5;
            break;
        case 'd':
            player.dexterity += 5;
            break;
        case 'i':
            player.intelligence += 5;
            break;
    }
}

int player_damage_dealt(){
    int max= 0, current;
    int *start;
    start = &player.strength;
    int i;
    for(i = 1; i <= 3; i++){
        if(item_stat() == i){
            current = item_power();
        } else{
            current = 0;
        }
        if (current + start[i-1] > max){
            max = current+ start[i-1];
        }
    }
    return max;
}
