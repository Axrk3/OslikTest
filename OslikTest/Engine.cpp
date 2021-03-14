#include "Engine.h"
#include <iostream>


Engine::Engine() {
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	window.create(VideoMode(resolution.x, resolution.y), "Game Engine v.1", Style::Fullscreen);

	backgroundTexture.loadFromFile("back.jpg");
	backgroundSprite.setTexture(backgroundTexture);

	rectSize.x = 32; rectSize.y = 32;
	rect.setSize(rectSize);
	
	lvl.changeLevel(map1);
}

void Engine::input() {
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		player.dx = -300;
	}
	else {
		player.dx = 0;
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		player.dx = 300;
	} 
	
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		player.Jump();
	}
	
}

void Engine::update(float time) {
	player.rect.left += player.dx * time;

	collision(0);

	if (!player.onGround) {
		player.dy += 1000 * time;
	}

	player.rect.top += player.dy * time;

	collision(1);

	if (player.rect.top > player.ground) {
		player.rect.top = player.ground;
		player.dy = 0;
		player.onGround = true;
	}
	player.sprite.setPosition(player.rect.left, player.rect.top);
}

void Engine::collision(int dir) {
	for (int i = player.getRect().top / 32; i < (player.getRect().top + player.getRect().height) / 32; i++) {
		for (int j = player.getRect().left / 32; j < (player.getRect().left + player.getRect().width) / 32; j++) {
			if (lvl.getMap()[i][j] == 'B') {
				
				if ((player.dx > 0) && (dir == 0)) player.setRect(0, j * 32 - player.getRect().width);
				if ((player.dx < 0) && (dir == 0)) player.setRect(0, j * 32 + 32);
				if ((player.dy > 0) && (dir == 1)) {
					player.setRect(1, i * 32 - player.getRect().height);
					player.dy = 0; player.onGround = true;
				}
				if ((player.dy < 0) && (dir == 1)) {
					player.setRect(1, i * 32 + 32);
					player.dy = 0;
				}
			}
		}
	}
}

void Engine::drawMap(String map[]) {

	for (int i = 0; i < 34; i++) {
		for (int j = 0; j < 40; j++) {
			if (map[i][j] == 'B') rect.setFillColor(Color::Black);
			else {
				rect.setFillColor(Color::White);
			}
			rect.setPosition(j * 32,i * 32);
			window.draw(rect);
		}
	}
}

void Engine::draw() {
	window.clear(Color::White);
	window.draw(backgroundSprite);
	drawMap(lvl.getMap());
	window.draw(player.getSprite());
	window.display();
}

void Engine::start() {
	Clock clock;
	while (window.isOpen()) {
		Time dt = clock.restart();
		float time = dt.asSeconds();
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case Event::Closed:
				window.close();
				break;

			case Event::KeyPressed : {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
				input();
				break;
			}
			case Event::KeyReleased: {
				input();
				break;
			}
			default:
				break;
			}
		}
		update(time);
		draw();
	}
}

