#include "GameObjects.h"
#include "Levels.h"

Player::Player() {
	stats.HP = 85;
	stats.ATK = 5;
	stats.DEF = 2;
	ground = 800;
	texture.loadFromFile("bob.png");
	sprite.setTexture(texture);
	sprite.setColor(Color::Green);
	rect = FloatRect(250, ground, 150, 192);
	dy = 0,dx = 0;
}

Enemy::Enemy() {
	stats.HP = 100;
	stats.ATK = 20;
	stats.DEF = 1;
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

Sprite Consumable::getSpriteInInventory() {
	return spriteInInventory;
}

Inventory::Inventory() {
	quantityConsum = 0, quantityEquip = 0;

	texture.loadFromFile("inventory.png");
	sprite.setTexture(texture);
	sprite.setPosition(480, 270);

	
	attackRect.setPosition(1248, 328);
	attackRect.setFillColor(Color::Red);
}

void Inventory::addItem(Consumable item, String itemName) {
	this->consum->name = itemName;
	this->consum->maxQuantity++;
	
	itemName += ".png";

	this->consum->textureInInventory.loadFromFile(itemName);
	this->consum->spriteInInventory.setTexture(this->consum->textureInInventory);
	this->consum->spriteInInventory.setPosition(543, 323);

	
}

void Inventory::addItem(Equipment item) {

}