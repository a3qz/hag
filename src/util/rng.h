#ifndef RNG_H
#define RNG_H

/* Constants for probabilities */

int rng_rand(int max); /* returns a random number in the range [0, max] */
int rng_roll(int droprate); /* returns 1 with probability 1/droprate, else 0 */
#endif
