#include "player.h"
#include <stdlib.h>
#include "gui.h"
#include "item.h"

static player_t player = {
    175, /* current hp*/
    175, /* max_hp */ 
    50,  /* y */
    50,  /* x */ 
    10,  /* strength */ 
    10,  /* dexterity */
    10,  /* intelligence */ 
    0,   /* current_exp */
    112, /* max_exp */ 
    1,   /* current_level */
    1000 /* luck */
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
    char res = gui_prompt("What stat would you like to increase? (s)trength, (d)exterity, or (i)ntelligence?", "sdi");
    player.current_level++;
    player.max_hp += player.max_hp/4;
    player.current_hp = player.max_hp;
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
    int current;
    int *start;
    int i;
    int max = 0;
    start = &player.strength;
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
    return rand()%max;
}
