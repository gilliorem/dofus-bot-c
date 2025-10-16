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

26.06.2025
1. Cereal pattern
	fix reap wheat to fully work on every map.
	fix common cereal pattern (4)

2. Change map.

*check_element() will not find the pattern on the first run but wil on the second run... need to check at least twice to be sure to catch the pattern.*

30.6.2025 - 1.07
1. Check element
	create_pattern_element(): Finish by 5:30
	*generic* Element_pattern struct: Finish by 5:45
	check_element()
	Create each of the 20 elements (Create one-test one): Finish by 7:00
		OK Ready_button_pattern OK
		OK Hammer_pattern 
		OK Scythe_pattern
		OK Red_arrow_icon_pattern
	//	Player_pattern > (color matrix vertical)
	//	Enemy_pattern > (color matrix)
	//	Red_tile_pattern
	//	Blue_tile_pattern
		OK Orange_counter_pattern
		OK Tactical_mode_icon_pattern > very small matrix (50x50)
	//	Light_grey_tile_pattern
	//	Dark_grey_tile_pattern
	//	Red_circle_pattern
	//	Blue_circle_pattern
		OK Boost_spell_one_pattern 
		OK Boost_spell_two_pattern 
		OK Boost_spell_three_pattern 
		OK Attack_spell_one_pattern 
		OK Attack_spell_two_pattern 
		OK Move_points_pattern	
		OK Action_point_pattern
		OK Pass_turn_button_pattern
		End_combat_window_pattern


7:08 6 elements created. 14 left.

-build smaller matrix
-check smaller element

-check bigger element
-having the 20 checks.

