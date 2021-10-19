#ifndef CONTROLS_H
#define CONTROLS_H

#include <ncurses.h>
#ifndef KEY_F
#define KEY_F(n)        (KEY_F0 + (n))
#endif

/* Normal movements */
#define KEY_MOVE_N        'j'
#define KEY_MOVE_N_BABBY  0x102
#define KEY_MOVE_W        'h'
#define KEY_MOVE_W_BABBY  0x104
#define KEY_MOVE_S        'k'
#define KEY_MOVE_S_BABBY  0x103
#define KEY_MOVE_E        'l'
#define KEY_MOVE_E_BABBY  0x105

/* Diagonal movement */
#define KEY_MOVE_NW       'b'
#define KEY_MOVE_NE       'n'
#define KEY_MOVE_SW       'y'
#define KEY_MOVE_SE       'u'

/* Run */
#define KEY_RUN_N        'J'
#define KEY_RUN_W        'H'
#define KEY_RUN_S        'K'
#define KEY_RUN_E        'L'
#define KEY_RUN_NW       'B'
#define KEY_RUN_NE       'N'
#define KEY_RUN_SW       'Y'
#define KEY_RUN_SE       'U'

/* Actions */
#define KEY_CLIMB_UP      '<'
#define KEY_CLIMB_DOWN    '>'
#define KEY_QWARF         'q'
#define KEY_EQUIP         'e'
#define KEY_INSPECT       'I'
#define KEY_FIGHT         'f'
#define KEY_BIDE          '.'
#define KEY_QUIT          KEY_F(4)
#define KEY_QUESTIONMARK  '?'

/* Scroll */
#define KEY_SCROLL_UP     '['
#define KEY_SCROLL_DOWN   ']'

#endif
