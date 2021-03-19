#pragma once
#include <SFML/Graphics.hpp>
#include "GameObjects.h"
#include "Levels.h"
#include <iostream>
#include "Battle.h"

using namespace sf;

class Engine {
private:
	RenderWindow window;
	Sprite backgroundSprite;
	Texture backgroundTexture;
	Font regularFont;
	Text regularText;
	Battle battle;
	float offsetX, offsetY;
	int blockSize;
	bool openInventory = false;
	bool openChest = false;
	void input();
	void update(float time);
	void draw();
	void drawMap(String map[]);
	void drawInventory();
	void collision(int dir);
	Player player;
	Level lvl;
	RectangleShape rect;
	Vector2f rectSize, resolution;
public:
	Engine();
	void start();

};