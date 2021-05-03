#pragma once
#include "Engine.h"

class Battle {
	Player player;
	Enemy *enemy;
	int enemyAmount, deadEnemy, playerAmount = 1;

	Vector2f resolution, currentPosition, barSize;
	Vector2i action;
	RectangleShape hpBar, outlineHP, *menuBar;
	bool isAction, isBlocked;

	Font font;
	Text attackText;
	
	Texture cursorTexture, menuTexture;
	Sprite cursorSprite, menuSprite;

public: 
	Battle(Player &_player, Enemy *&_enemy, int _enemyAmount);
	void battleStart(RenderWindow &window);
	void drawElements(RenderWindow &window);
	void actionProcessing(RenderWindow &window);
	void menuInitialization();
	void cursorInitialization();
	void unitInitialization();
	void input();

	//======================
	int battleEnd(RenderWindow &window);
	void defenceUp(Character &defender);
	void defenceDown(Character &defender);
	//======================
	void attack(Character &attacker, Character &defender, int speedX, int speedY, RenderWindow &window);
	int chooseEnemy(RenderWindow &window);
};