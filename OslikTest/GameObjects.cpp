#include "GameObjects.h"
#include "Levels.h"

Player::Player() {
	characteristics.HP = 10;
	ground = 800;
	texture.loadFromFile("bob.png");
	sprite.setTexture(texture);
	rect = FloatRect(500, ground, 150, 192);
	dy = 0,dx = 0;
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

void Player::Jump() {
	if (dy == 0) {
		dy = -750;
	}
}

Inventory::Inventory() {
	quantityConsum, quantityEquip = 0;
	scale.x = 960; scale.y = 640;
	rect.setSize(scale);
}

void Inventory::addItem(Consumable item) {

}
void Inventory::addItem(Equipment item) {

}