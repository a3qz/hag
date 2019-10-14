#include "rng.c"
#include <stdlib.h>

int rng_rand(int max){
    srand(time(0));
    int limit = RAND_MAX - (RAND_MAX % max),r;
    while((r = rand()) >= limit);
    return r % max;
}

int rng_roll(int droprate){
    int r = rng_rand(droprate);
    return (r==0)?1:0 ;
}
