#include "pattern.h"
#include "types.h"

ElementPattern Ready_button_pattern = 
{
	.color = {252, 109, 36},
	.width = 30,
	.tol = {30,10,30},
	.pos = {1500, 800},
	.name = "Ready button pattern"
};

ElementPattern Hammer_pattern = {

	.color = {255,255,255},
	.width = 6,
	.tol = {10,10,10},
	.pos = {1200, 943},
	.name = "Hammer pattern"
};


ElementPattern Scythe_pattern = {

	.color = {255,255,255},
	.width = 6,
	.tol = {10,10,10},
	.pos = {1270, 943},
	.name = "Scythe pattern"
};

ElementPattern Red_arrow_icon_pattern = {

	.color = {240,50,45},
	.width = 10,
	.tol = {15,15,15},
	.pos = {1580, 730},
	.name = "Red arrow icon pattern"
};

/*
 * Different checking zone (big matrix)
ElementPattern Player_pattern = {

	.color = {137,10,10},
	.width = 10,
	.tol = {10,15,15},
	.pos = {1561, 711},
	.name = "Red arrow icon pattern"
};
*/

ElementPattern Orange_counter_pattern = {

	.color = {253,109,36},
	.width = 20,
	.tol = {15,15,15},
	.pos = {1050,860},
	.name = "Orange counter pattern"
};

ElementPattern Tactic_icon_pattern = {

	.color = {253,109,36},
	.width = 25,
	.tol = {15,15,15},
	.pos = {1033,844},
	.name = "Orange counter pattern"
};

ElementPattern Boost_spell_one_pattern = {

	.color = {168,134,42},
	.width = 6,
	.tol = {10,10,10},
	.pos = {1220, 943},
	.name = "Boost spell one:Compulsion"
};

ElementPattern Boost_spell_two_pattern = {

	.color = {168,134,42},
	.width = 6,
	.tol = {10,10,10},
	.pos = {1270, 943},
	.name = "Boost spell two:Bravery"
};

ElementPattern Boost_spell_three_pattern = {
	.color = {168,134,42},
	.width = 6,
	.tol = {10,10,10},
	.pos = {1320, 943},
	.name = "Boost spell three:Increase"
};

ElementPattern Attack_spell_one_pattern = {
	.color = {108,57,31},
	.width = 6,
	.tol = {10,10,10},
	.pos = {1370, 943},
	.name = "Attack spell one:Pression"
};

ElementPattern Attack_spell_two_pattern = {
	.color = {175,45,48},
	.width = 6,
	.tol = {10,10,10},
	.pos = {1420, 943},
	.name = "Attack spell two:Sword of fate"
};

ElementPattern Action_points_pattern = {
	.color = {27,41,249},
	.width = 6,
	.tol = {10,10,10},
	.pos = {950, 880},
	.name = "Action points"
};

ElementPattern Move_points_pattern = {
	.color = {3,101,15},
	.width = 6,
	.tol = {10,10,10},
	.pos = {1100, 880},
	.name = "Move points"
};

ElementPattern Pass_turn_pattern = {
	.color = {255,255,255},
	.width = 20,
	.tol = {10,10,10},
	.pos = {1160, 1020},
	.name = "Pass turn"
};
