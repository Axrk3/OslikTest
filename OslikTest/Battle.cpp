#include "Battle.h"

Battle::Battle() {
}

void Battle::Start(RenderWindow &window, Player &_player, Enemy& _enemy) {
	enemy = &_enemy; player = &_player;
	while (isAlive(*player) && isAlive(*enemy)) {
		window.clear(Color::White);
		window.draw(player->getSprite());
		window.draw(enemy->getSprite());
		window.display();
		
		input();
	}

	return;
}

void Battle::input() {
	if (Keyboard::isKeyPressed(Keyboard::F)) enemy->stats.HP -= player->stats.ATK;
	if (Keyboard::isKeyPressed(Keyboard::G)) enemy->stats.HP -= player->stats.ATK + 3;
}

bool Battle::isAlive(Character creature) {
	if (creature.stats.HP > 0)
		return 1;
	else
		return 0;
}