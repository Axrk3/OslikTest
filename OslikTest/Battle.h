#pragma once
#include "Engine.h"

class Battle {
	Player player;
	Enemy enemy;

	Vector2f resolution, currentPosition;
	RectangleShape menu, *menuBar, cursor, *hpBar, *outlineHP;
	FloatRect endMenu;
	int action;
	bool isAttacked;
	bool isBlocked;
	Font font;
	Text *text;
	
public: 
	Battle(Player &_player, Enemy &_enemy);
	void battleStart(RenderWindow &window);
	void drawElements(RenderWindow &window);
	void actionProcessing();
	void menuInitialization();
	void textInitialization();
	void cursorInitialization();
	void unitInitialization();
	void input();

	//======================
	int battleEnd(RenderWindow &window);
	void defenceUp(Character &defender);
	void defenceDown(Character &defender);
	//======================
	void attack(Character &attacker, Character &defender);
};