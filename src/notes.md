16.06

## CEREAL COLOR PATTERN RECOGNITION

### Problem: Color changes on different screen.
FIX: Use a bigger pattern (100px pattern) (25y x 4x);

Before doing this, I need to update my pattern recognition method.
instead of checking `xxxx`
need to check
x
x
xx
x
x

1. Should I zone-check ?
Yes and no.

### Do not cross the whole map
-> Can go through the screen looking at only 1 of 4 pixel
-> Even better: can check randomly on the screen and stop as I find one.
-> The best of all: can check 10x10 zone randomly. not randomly.
can go 
-> pixel match: look for the pattern in a 10x10 zone around that pixel
xx1xxx
xx1xxx
xx11xx
x121xx
xx1xx1

*move mouse to each pixel matching the color*

## Combat logic:
Map scan every new player's turn
Count tiles
change to 89-grey pixel pattern into a 'triangle pattern'
           x
	  xxx
	 xxxxx
	xxxxxxx
	 xxxxx
	  xxx
	   x
so it counts every tiles

## Players

### Spot player
Change the 90 pixel pattern into a 4x4 red pixel pattern
if we have this 4x4 red pattern (during combat state) -> player is in map -> in *xy* -> 
*xy* giving us a tile player is in *xy:center of xth tile*

17.06
1. Update wheat color pattern. ok
	xxxx 

	x
	x
	x
	x

R: 166-174
G: 97-105
B: 19-21

1.1. Recognize pattern on y axis. *ok*
2. Spot 100% of the wheat in map. *80%+* -> good enough  for now.

18.06
1. Update following color pattern:
- hop
- flax

### COMBAT
- Find total number of tiles
	>Redefine tile color-pattern
- Find player
	>Redefine player color-pattern
- Find enemy
	>Redefine enemy color-pattern

- Calculate distance
	>Distance in tile
- Find path
	>Draw path.
	>Move
