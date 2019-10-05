#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "args.h"

void parse_args(int argc, char **argv) {
    srand(time(NULL));

    while (1) {
        struct option long_options[] = {
            {"help", no_argument,       NULL, 'h'},
            {"seed", required_argument, NULL, 's'},
            {0, 0, 0, 0}
        };
        int c = getopt_long(argc, argv, "hs:", long_options, NULL);
        unsigned long seed;

        if (c == -1) {
            break;
        }

        switch (c) {
            case 'h':
                printf("hag, an ncurses procedurally-generated dungeon crawler.\n\n");
                printf("Usage: %s [options]\n", argv[0]);
                printf("-h, --help        Show this help message\n");
                printf("-s, --seed <seed> RNG seed to use\n");
                exit(EXIT_SUCCESS);
            case 's':
                seed = strtoul(optarg, NULL, 10);

                if (errno == ERANGE || seed > UINT_MAX) {
                    fprintf(stderr, "Invalid seed.\n");
                    exit(EXIT_FAILURE);
                }

                srand(seed);
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }
}
