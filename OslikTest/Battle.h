#pragma once
#include <SFML/Graphics.hpp>
#include "GameObjects.h"

class Battle {
private:
	Player *player;
	Enemy *enemy;
	RenderWindow *window;

public:
	Battle(RenderWindow &_window, Player &_player, Enemy &_enemy);
	void Start();
	bool isAlive(Character &creature);

};