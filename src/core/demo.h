#ifndef DEMO_H
#define DEMO_H
int demo_next(void);
void demo_start(int mode, char* fname);
#define DEMO_NONE 0
#define DEMO_REPLAY 1
#define DEMO_RECORD 2
#define DEMO_VERSION 0
#define DEMO_DEFAULT_FILE ".demo.hag"
/* TODO: do we need a demo_close? */
#endif