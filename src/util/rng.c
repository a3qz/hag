#include "rng.h"
#include <stdlib.h>

int rng_rand(int max){
    int limit = RAND_MAX - (RAND_MAX % (max + 1)),r;
    while((r = rand()) >= limit);
    return r % (max + 1);
}

int rng_roll(int droprate){
    int r = rng_rand(droprate);
    return (r==0)?1:0 ;
}
