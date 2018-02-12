from __future__ import print_function
import random

NUM_ROOMS = 30
MAX_ROOM_X = 30
MIN_ROOM_X = 3
MAX_ROOM_Y = 30
MIN_ROOM_Y = 3
BOARD_X = 100
BOARD_Y = 200
board = []

# good use.  unforutnatley baiscally entials beelining until it can straightaway or diagonal.  Can change that by adding different amounts of increase, im just lazy  
def connectpoints2(board, newcenterx, newcentery, oldcenterx, oldcentery):
	# calculate the difference
	xdiff = newcenterx-oldcenterx
	ydiff = newcentery-oldcentery
	realx = newcenterx
	realy = newcentery
	print(xdiff, end="\t")
	print(ydiff)

	# draw one block in the path on the way to the next center
	while abs(xdiff) > 0 or abs(ydiff) > 0:
		if abs(xdiff) > abs(ydiff):
			if xdiff > 0:
				xdiff -= 1
				realx -= 1
			elif xdiff < 0:
				xdiff += 1
				realx += 1
			board[realx][realy] = " "
		else:
			if ydiff > 0:
				ydiff -= 1
				realy -= 1
			elif ydiff < 0:
				ydiff += 1
				realy += 1

			board[realx][realy] = " "

	

# Main here

# Fill blank board
for i in range(BOARD_X):
	board.append([])
	for y in range(BOARD_Y):
		board[i].append(u'\u2588')

xcenter = 0
ycenter = 0
xcenter2 = 0
ycenter2 = 0

# make NUM_ROOMS rooms
for _ in range(NUM_ROOMS):

	# choose height and width
	xlen = random.randint(0,MAX_ROOM_X)
	ylen = random.randint(0,MAX_ROOM_Y)
	
	# choose starting position
	xpos = random.randint(1,BOARD_X-xlen-1)
	ypos = random.randint(1,BOARD_Y-ylen-1)

	# get center of that square
	xcenter = xpos+xlen/2
	ycenter = ypos+ylen/2

	# fill that box with squares
	for x in range(xlen):
		for y in range(ylen):
			board[x+xpos][y+ypos] = " "

	# unless it is the first square, connect this to the previously generated square
	if xcenter2 != 0:
		connectpoints2(board, xcenter, ycenter, xcenter2, ycenter2)

	# set for next iteration
	xcenter2 = xcenter
	ycenter2 = ycenter

# print out board
for i in board:
	for y in i:
		print(y.encode('utf-8'),end="")
	print("")

