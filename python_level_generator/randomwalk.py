from __future__ import print_function
import random

NUM_TILES = 10000
MAX_ROOM_X = 30
MIN_ROOM_X = 3
MAX_ROOM_Y = 30
MIN_ROOM_Y = 3
BOARD_X = 100
BOARD_Y = 200
board = []


# fill with blocks
for i in range(BOARD_X):
	board.append([])
	for y in range(BOARD_Y):
		board[i].append(u'\u2588')

xcenter = 0
ycenter = 0
xcenter2 = 0
ycenter2 = 0

startx = BOARD_X/2
starty = BOARD_Y/2

# place NUM_TILES in random directions
for _ in range(NUM_TILES):
    direction = random.choice([1,2,3,4])
    if direction == 1:
        startx += 1
    elif direction == 2:
        startx -= 1
    elif direction == 3:
        starty += 1
    elif direction == 4:
        starty -= 1

    # if going off board, reset at the middle
    if startx > BOARD_X-1 or startx < 1 or starty > BOARD_Y-1 or starty < 1:
        startx = BOARD_X/2
        starty = BOARD_Y/2
    board[startx][starty] = " "
	

for i in board:
	for y in i:
		print(y.encode('utf-8'),end="")
	print("")

