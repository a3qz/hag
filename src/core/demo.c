#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include "demo.h"
#include "args.h"
#include "controls.h"
#include "main.h"

static void demo_write_header(void);
static void demo_read_header(void);

static FILE* read_from = 0;
static FILE* write_to = 0;

static int demo_speed = 300;

#ifndef __HAS_USLEEP__
void usleep(long); /* needed because headers are big sad */
#endif

int demo_next(void)
{
    int move = 0;
    if (read_from) {
        fread(&move, sizeof(move), 1, read_from);
        usleep(1000 /*ms to us*/ * demo_speed /*ms*/);
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
    int halloween;
    unsigned long s;
    fread(&demo_version, sizeof(demo_version), 1, read_from);
    fread(&s, sizeof(s), 1, read_from);
    if (demo_version != DEMO_VERSION) {
        fprintf(stderr, "File demo version (%d) does not match application version (%d)!\n", demo_version, DEMO_VERSION);
        exit(1);
    }
    set_seed(s);
    fread(&halloween, sizeof(halloween), 1, read_from);
    fread(&halloween, sizeof(halloween), 1, read_from);
    set_halloween(halloween);
}


static void demo_write_header(void)
{
    unsigned long s = get_seed();
    int demo_version = DEMO_VERSION;
    int command_char = COMMAND_CHAR;
    int one = is_halloween();
    fwrite(&demo_version, sizeof(demo_version), 1, write_to);
    fwrite(&s, sizeof(s), 1, write_to);
    fwrite(&command_char, sizeof(command_char), 1, write_to);
    fwrite(&one, sizeof(one), 1, write_to);
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
        break;
    case DEMO_RECORD:
        write_to = fopen(fname, "w");
        break;
    }
}

void demo_header()
{
    if (read_from) {
        demo_read_header();
    }
    if (write_to) {
        demo_write_header();
    }
}

void demo_set_speed(int s)
{
    demo_speed = s;
}
