#pragma once
#include <SFML/Graphics.hpp>
#include "GameObjects.h"
#include "Levels.h"
#include "Battle.h"
#include <iostream>

using namespace sf;

class Engine {
private:
	RenderWindow window;
	Sprite backgroundSprite;
	Texture backgroundTexture;
	Font regularFont;
	Text regularText;
	float offsetX, offsetY, prefTime = 0, time;
	int blockSize;
	bool openInventory = false;
	bool openChest = false;
	bool onFight = false;
	void input();
	void update(float time);
	void draw();
	void drawMap(String map[]);
	void drawInventory();
	void collision(int dir);
	Mutex mutex;
	Player player;
	Level lvl;
	RectangleShape rect;
	Vector2f rectSize, resolution;
	Consumable potion;
public:
	Engine();
	void start();
};