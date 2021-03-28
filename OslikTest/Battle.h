#pragma once
#include "Engine.h"

class Battle {
	Player player;
	Enemy enemy;
public: 
	Battle(Player &_player, Enemy &_enemy);
	void StartBattle(RenderWindow& window);
};