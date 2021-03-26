#include "GameObjects.h"
#include "Levels.h"

Player::Player() {
	stats.HP = 85;
	stats.ATK = 7;
	ground = 800;
	texture.loadFromFile("bob.png");
	sprite.setTexture(texture);
	sprite.setColor(Color::Green);
	rect = FloatRect(250, ground, 150, 192);
	dy = 0,dx = 0;
}

Enemy::Enemy() {
	stats.HP = 100;
	stats.ATK = 5;
	texture.loadFromFile("bob.png");
	sprite.setTexture(texture);
	sprite.setColor(Color::Red);
	rect = FloatRect(250, 1350, 150, 192);
}

// id: 0 - x, 1 - y
void GameObject::setRect(int id,int value) {
	if (id == 0) {
		this->rect.left = value;
	} else {
		this->rect.top = value;
	}
}

FloatRect GameObject::getRect() {
	return rect;
}

Sprite GameObject::getSprite() {
	return sprite;
}

Character::characteristics Character::getStats() {
	return this->stats;
}

void Player::Jump() {
	if (dy == 0) {
		dy = -750;
	}
}

Consumable::Consumable() {
	name = "";
	maxQuantity = 0;
}

Inventory::Inventory() {
	quantityConsum = 0, quantityEquip = 0;
	scale.x = 960; scale.y = 640;
	rect.setSize(scale);
}

void Inventory::addItem(Consumable item, String itemName) {
	this->consum->name = itemName;
	this->consum->maxQuantity++;
}
void Inventory::addItem(Equipment item) {

}