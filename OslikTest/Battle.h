#pragma once
#include <SFML/Graphics.hpp>
#include "GameObjects.h"

class Battle {
private:
	Player *player;
	Enemy *enemy;

public:
	Battle();
	void Start(RenderWindow &window, Player &_player, Enemy& _enemy);
	bool isAlive(Character creature);
	void input();

};