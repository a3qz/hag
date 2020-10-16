#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "args.h"
#include "demo.h"
static unsigned long seed;
void parse_args(int argc, char **argv)
{
    int demo_started = 0;
    set_seed(time(NULL));

    while (1) {
        struct option long_options[] = {
            { "help", no_argument, NULL, 'h' },
            { "seed", required_argument, NULL, 's' },
            { "play", optional_argument, NULL, 'r' },
            { "record", optional_argument, NULL, 'w' },
            { 0, 0, 0, 0 }
        };
        int c = getopt_long(argc, argv, "hs:r?w?", long_options, NULL);

        if (c == -1) {
            break;
        }

        switch (c) {
        case 'h':
            printf
                ("hag, an ncurses procedurally-generated dungeon crawler.\n\n");
            printf("Usage: %s [options]\n", argv[0]);
            printf("-h, --help        Show this help message\n");
            printf("-s, --seed   <seed> RNG seed to use\n");
            printf("-r, --play   [file] demo file to replay\n");
            printf("-w, --record [file] file to save demo to\n");
            printf("\n\n--play and --record take an optional file - if these flags are used but no file is given, .demo.hag is used instead.\n");
            exit(EXIT_SUCCESS);
        case 's':
            seed = strtoul(optarg, NULL, 10);

            if (errno == ERANGE || seed > UINT_MAX) {
                fprintf(stderr, "Invalid seed.\n");
                exit(EXIT_FAILURE);
            }

            set_seed(seed);
            break;
        case 'r':
            demo_start(DEMO_REPLAY, optarg);
            demo_started = 1;
            break;
        case 'w':
            demo_start(DEMO_RECORD, optarg);
            demo_started = 1;
            break;
        default:
            exit(EXIT_FAILURE);
        }
    }
    if (!demo_started) {
        demo_start(DEMO_NONE, 0);
    }
}

void set_seed(unsigned long s)
{
    seed = s;
    srand(s);
}

unsigned long get_seed(void)
{
    return seed;
}