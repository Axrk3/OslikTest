#include "GameObjects.h"

Player::Player() {
	speed = 400;
	ground = 800;
	texture.loadFromFile("bob.png");
	sprite.setTexture(texture);
	rect = FloatRect(500, ground, 150, 192);
	dy = 0;
}

Sprite GameObject::getSprite() {
	return sprite;
}

void Player::moveLeft() {
	leftPressed = true;
}

void Player::runLeft() {
	leftRun = true;
}

void Player::moveRight() {
	rightPressed = true;
}

void Player::runRight() {
	rightRun = true;
}

void Player::stopLeft() {
	leftPressed = false;
	leftRun = false;
}

void Player::stopRight() {
	rightPressed = false;
	rightRun = false;
}

void Player::Jump() {
	if (onGround) {
		dy = -500;
		onGround = false;
	}
}

void Player::update(float time) {

	if (rightPressed) {
		rect.left += speed * time;
		if (rightRun) {
			rect.left += speed * time;
		}
	}

	if (leftPressed) {
		rect.left -= speed * time;
		if (leftRun) {
			rect.left -= speed * time;
		}
	}

	if (!onGround) {
		dy += 1000 * time;
	}

	rect.top += dy * time;

	if (rect.top > ground) {
		rect.top = ground;
		dy = 0;
		onGround = true;
	}
	sprite.setPosition(rect.left, rect.top);
}