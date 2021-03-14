#pragma once
#include <SFML/Graphics.hpp>
#include "GameObjects.h"
#include "Levels.h"
#include <iostream>

using namespace sf;

class Engine {
private:
	RenderWindow window;
	Sprite backgroundSprite;
	Texture backgroundTexture;
	float offsetX, offsetY;
	void input();
	void update(float time);
	void draw();
	void drawMap(String map[]);
	void collision(int dir);
	Player player;
	Level lvl;
	RectangleShape rect;
	Vector2f rectSize;
public:
	Engine();
	void start();

};