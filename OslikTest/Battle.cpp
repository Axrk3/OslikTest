#include "Battle.h"

Battle::Battle() {
}

void Battle::Start(RenderWindow &window, Player &_player, Enemy& _enemy) {
	enemy = &_enemy; player = &_player;
	while (true) {
		window.clear(Color::White);
		window.draw(player->getSprite());
		window.display();
		player->stats.HP = 0;
		if (Keyboard::isKeyPressed(Keyboard::C)) break;
	}
}


bool Battle::isAlive(Character &creature) {
	if (&creature.stats.HP > 0)
		return 1;
	else
		return 0;
}