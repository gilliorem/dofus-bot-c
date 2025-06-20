20.06.2025

0. check state:
	create a function that check for character state (normal or combat)
	check state needs an element in frame that is different when in Normal mode with combat mode
	It should be a static element
	the 2 last icons above the ready button (going right to left)
	*notes that the ready button become the fight participants-mini-frame after the combat has started*
	zone to check: around the red-arrow pointing down: 
	>x:1561 y:711 w:100 h:100 (small matrix)
	>RGB Ref: R >= 200 G >= 40 <= 60 B >= 40 <= 50
	>REF: 240 50 45: TOLERANCE: 15

1. check weapon
	base on the character state, create a function that will check the current
	weapon equip and if it is the correct one
2. equip weapon
	based on check weapon, will equip the needed weapon.


