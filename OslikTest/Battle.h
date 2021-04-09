#pragma once
#include "Engine.h"

class Battle {
	Player player;
	Enemy enemy;

	Vector2f resolution, currentPosition;
	RectangleShape menu, *menuBar, cursor, *hpBar, *outlineHP;
	int action;
	bool isAttacked;
	Font font;
	Text *text;
	
public: 
	Battle(Player &_player, Enemy &_enemy);
	void battleStart(RenderWindow& window);
	void drawElements(RenderWindow& window);
	void actionProcessing();
	void menuInitialization();
	void textInitialization();
	void cursorInitialization();
	void unitInitialization();
	void input();
	void attack(Character &attacker, Character &defender);
};