#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include "demo.h"
#include "args.h"

static void demo_write_header(void);
static void demo_read_header(void);

static FILE* read_from = 0;
static FILE* write_to = 0;

void usleep(long); /* needed because headers are big sad */

int demo_next(void)
{
    int move = 0;
    if (read_from) {
        fread(&move, sizeof(move), 1, read_from);
        usleep(1000 /*ms to us*/ * 300 /*ms*/);
    }
    if (!move) {
        move = getch();
    }
    if (write_to) {
        fwrite(&move, sizeof(move), 1, write_to);
    }
    return move;
}

static void demo_read_header()
{
    int demo_version;
    unsigned long s;
    fread(&demo_version, sizeof(demo_version), 1, read_from);
    fread(&s, sizeof(s), 1, read_from);
    /* TODO: fail if demo version is wrong */
    set_seed(s);
}


static void demo_write_header(void)
{
    unsigned long s = get_seed();
    int demo_version = DEMO_VERSION;
    fwrite(&demo_version, sizeof(demo_version), 1, write_to);
    fwrite(&s, sizeof(s), 1, write_to);
}

void demo_start(int mode, char* fname)
{
    if (!fname) {
        fname = DEMO_DEFAULT_FILE;
    }
    if (read_from) {
        fclose(read_from);
        read_from = 0;
    }
    if (write_to) {
        fclose(write_to);
        write_to = 0;
    }
    switch (mode) {
    default:
        break;
    case DEMO_REPLAY:
        read_from = fopen(fname, "r");
        demo_read_header();
        break;
    case DEMO_RECORD:
        write_to = fopen(fname, "w");
        demo_write_header();
        break;
    }
}