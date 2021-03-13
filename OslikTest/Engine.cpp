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
	
}

void Engine::input() {
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::LShift)) {
		player.runLeft();
	}
	else if (Keyboard::isKeyPressed(Keyboard::A)) {
		player.stopLeft();
		player.moveLeft();
	}
	else {
		player.stopLeft();
	}

	if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::LShift)) {
		player.runRight();
	}
	else if (Keyboard::isKeyPressed(Keyboard::D)) {
		player.stopRight();
		player.moveRight();
	}
	else {
		player.stopRight();
	}
	

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		player.Jump();
	}
	
}

void Engine::update(float dtAsSeconds) {
	player.update(dtAsSeconds);
}

void Engine::drawMap() {

	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 40; j++) {
			if (i != j) rect.setFillColor(Color::Black);
			else {
				rect.setFillColor(Color::Green);
			}
			rect.setPosition(j * 32,i * 32);
			window.draw(rect);
		}
	}
}

void Engine::draw() {
	window.clear(Color::White);
	window.draw(backgroundSprite);
	drawMap();
	window.draw(player.getSprite());
	window.display();
}

void Engine::start() {
	Clock clock;
	while (window.isOpen()) {
		Time dt = clock.restart();
		float dtAsSeconds = dt.asSeconds();
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
		update(dtAsSeconds);
		draw();
	}
}