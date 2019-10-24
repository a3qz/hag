# hag
An ncurses procedurally generated dungeon crawler

## Story and History

In our game, A Hag amongst the Glyphs, you play as a nameless adventurer.  You begin the game with no almost no skill and a sword so blunt it literally does not help you defeat enemies at all.  You were quite content with you life as a simple farmer, until one day, an evil Hag descended upon your village and turned all of the surrounding property into a wasteland, including your farm!  You are the only one brave (or stupid) enough to try and take revenge on the hag.  As you progress through the dangerous dungeon, you find and combat enemies of increasing power and ferocity.  You also may find potions and weapons on the journey, these may help you but also may hurt you - so beware!  If you reach the end of the dungeon, you must battle the Hag to the death.  Kill her, and your vengeance is delivered! If you are lucky, maybe you will be able to reverse her magic, too.  

The game Rogue is a dungeon crawler adventure game that was initially released in 1980.  Thematically, it was inspired by classic medieval and dungeon crawling media, primarily Dungeons and Dragons and Lord of the Rings.  Its features that have defined its through into the games of today are its mechanic of permadeath, where your character only has one life and you must start a new game each time you play, and its mechanic of procedurally generating level layouts and enemy and item placements.  Our game includes both of those mechanics.  In addition, Rogue used the curses library and ascii art in order to represent its game state to the user.  Needless to say, the majority of modern roguelikes have eschewed this type of graphical representation in favor of more modern game development stacks and graphics libraries.  However, we have not done so, and developed our game with the ncurses library and in full compatibility with the C 89 standard.  We have also retained thematic conformity with the norm for the genre, using enemy names only from the high fantasy tradition.  We have also kept our general plot in this tradition as well, as you play as a nameless adventurer delving to the bottom of a dungeon in order to confront an evil monster, and you must overcome a myriad of enemies and grow in your own abilities in order to reach the end.  


## Installation

If you don't have `libncurses5-dev`, install it

Then, clone this repo and run `make`

Finally, run the executable `./out/hag`


## Controls:

Press `ESC` to shows controls in game.

### Movement:

			h = left

			j = down

			k = up

			l = right

			y = up left

			u = up right

			b = down left

			n = down right


### Combat:

			walk into the enemy you want to attack

### Item:

			e = pickup/swap with item on ground

### Stairs:

			< = go up an up staircase

			> = do down a down staircase


### Leveling:

		on levelup, press:

			s to increase strength

			d to increase dexterity

			i to increase intelligence


### Death:

		on death, press space to exit

### Exit:

		to exit, press F4
