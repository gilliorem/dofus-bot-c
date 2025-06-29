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

### COMBAT STATE
- Initial element used to determine the state:
Ready button.
Problem with this detection-type:
The button is visible only during the *placement* phase.
In case of check failling during this phase, we would lose our chance for later checks. We can improve the checking by looking for a static-element that remain here during the 2 combat phases.

**VIUSAL ELEMENTS**
> Ready button
> 5+ Icon above ready button
> Orange visual time counter (+ give me the info that is my turn)
> Red tiles and blue tiles accross the fight-map

**Combat has started**
> AP and MP (static element) and same color
> Spells (static) different color on hover or depends on AP
> Pass my turn button same color
> Surrender flag (static)
> Red and blue circle (moving) -will also give me pos info.

Scenario: 
Reap wheat
>*2 checks*
	>Ready button
	>Red tiles and blue tiles
>One or more of the elements are presents:
	>Player is in Combat mode.
>None of the element are present:
	>Player is in Normal mode.

>Combat mode
	>Check hammer
	>Equip hammer
	>Check player pos
	>Check enemy pos
	>Check red tiles
	>Find smallest distance between enemy and closest-red-tile
	>Place on the closest-to-enemy-red-tile
	>Check for orange counter
		*no-orange-counter*:
			-not in fight
			-fight has already started (enemy's turn)

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

### WHY IS THIS PROJECT TAKING MORE MORE AND TIME AND HOW TO FASTER THE PROCESS
The more I code this project, the more there is to code. The more issue and bugs popping from every corner.
-
	Pattern finding algo (hor/ver/rand...)
	Icon checking (ready button, arrow)
	Structural elements (Rgb, Rgb_pattern, Element, Ready_button)
	Path finding
	Gui
	...
The list simply does not stop.
But I need to stop go across my code and fix this and this and this **RANDOMLY**
I need a bigger plan that every changement I make is justified and follow the rules accordingly.

Here we go for the plan:
Just to make things clear, all these things needs to be fixed. And they are gonna be. but not **RANDOMLY**.
The first idea is still to make a working bot. everything else is secondary. 

Now. I need to focus on 1 thing: The normal mode and combat mode.
I need to be able to spot the switching state.
NORMAL > COMBAT
COMBAT > NORMAL

To perform the NORMAL to COMBAT I perform 2 check:
	The ready button: After each reap I check whether I can see the ready button
		No > Normal mode (Keep reaping)
		Yes > Combat mode (Switch to weapon, detect enemy, detect player, place the closest, click ready button)
	While I'm still in Combat mode > Check for the red-arrow-icon in the bottom right corner
		Yes > Still in combat mode (Check who's turn is it. My turn>check pos>get closer or attack)
		No > Back to Normal mode: Check any window, equip the scythe and reap some more.


In this specific case I need to check at least 3 elements on map
	The ready button
	The Hammer
	The Scythe
	The red-arrow-icon
	The player (different from red tile check)
	The ennemy (different from blue tile check)
	The red tiles
	The blue tiles
	The orange in the the circle (player's turn)
	The Tactical-mode-icon
	The light grey tile
	The dark grey tile
	The red circle
	The blue circle
	The boost spell 1-2-3
	The Attack spell 1-2
	The Move points
	The Action points
	The Pass-turn-button
	The end-combat window
	The info-window (in case I Level-up)
--------------------------- --------------------------- ---------------------------
