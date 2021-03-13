#pragma once
#include <SFML/Graphics.hpp>
#include "GameObjects.h"

using namespace sf;

class Engine {
private:
	RenderWindow window;
	Sprite backgroundSprite;
	Texture backgroundTexture;

	void input();
	void update(float dtAsSeconds);
	void draw();
	void drawMap();
	Player player;
	Level lvl1;
	RectangleShape rect;
	Vector2f rectSize;
public:
	Engine();
	void start();

};