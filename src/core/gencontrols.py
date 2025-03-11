#!/bin/env python3

keys = """
/* Normal movements */
KEY(MOVE_N,        'j')
KEY(MOVE_N_BABBY,  0x102)
KEY(MOVE_W,        'h')
KEY(MOVE_W_BABBY,  0x104)
KEY(MOVE_S,        'k')
KEY(MOVE_S_BABBY,  0x103)
KEY(MOVE_E,        'l')
KEY(MOVE_E_BABBY,  0x105)

/* Diagonal movement */
KEY(MOVE_NW,       'b')
KEY(MOVE_NE,       'n')
KEY(MOVE_SW,       'y')
KEY(MOVE_SE,       'u')

/* Run */
KEY(RUN_N,         'J')
KEY(RUN_W,         'H')
KEY(RUN_S,         'K')
KEY(RUN_E,         'L')
KEY(RUN_NW,        'B')
KEY(RUN_NE,        'N')
KEY(RUN_SW,        'Y')
KEY(RUN_SE,        'U')

/* Actions */
KEY(CLIMB_UP,      '<')
KEY(CLIMB_DOWN,    '>')
KEY(QWARF,         'q')
KEY(EQUIP,         'e')
KEY(INSPECT,       'I')
KEY(FIGHT,         'f')
KEY(BIDE,          '.')
KEY(QUIT,          KEY_F(4))
KEY(QUESTIONMARK,  '?')

/* Scroll */
KEY(SCROLL_UP,     '[')
KEY(SCROLL_DOWN,   ']')
"""

import re
pattern = r'KEY\(\s*([A-Z_]+)\s*,\s*(.*)\s*\)'
actions = [];
with open('gencontrols.h', 'w+') as f:
    for line in keys.split("\n"):
        match = re.match(pattern, line)
        if not match: continue
        action, key = match.groups()
        print(f"int KEY_{action} = {key};")
        print(f"#define ACTION_{action} ({key})")
        actions.append(action)
    print("int control_get_key(char ch) {")
    for action in actions:
        print(f"\tif (ch == KEY_{action}) return ACTION_{action}")
    print("\treturn 0;\n}")
        

