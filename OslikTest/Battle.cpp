#include "Battle.h"

Battle::Battle(RenderWindow &_window, Player &_player, Enemy &_enemy) {
	
	player = &_player;
	enemy = &_enemy;
}

void Battle::Start() {
	while (isAlive(*player) && isAlive(*enemy)) {
		window->clear(Color::White);
		
	}
}


bool Battle::isAlive(Character &creature) {
	if (&creature.stats.HP > 0)
		return 1;
	else
		return 0;
}