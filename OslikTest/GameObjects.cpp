#include "GameObjects.h"
#include "Levels.h"

Player::Player() {
	stats.HP = 85;
	stats.ATK = 14;
	stats.DEF = 4;
	ground = 800;
	texture.loadFromFile("bob.png");
	sprite.setTexture(texture);
	sprite.setColor(Color::Green);
	rect = FloatRect(250, ground, 150, 192);
	dy = 0,dx = 0;
}

Enemy::Enemy() {
	stats.HP = 20;
	stats.ATK = 10;
	stats.DEF = 3;
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

bool Character::isAlive() {
	if (this->stats.HP <= 0)
		return 0;
	else
		return 1;
}

void Player::Jump() {
	if (dy == 0) {
		dy = -750;
	}
}

Consumable::Consumable() {
	rect.height = rect.width = 64;
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

	
	attackRect.setPosition(sprite.getPosition().x + 768, sprite.getPosition().y + 58);
	attackRect.setFillColor(Color::Red);
	defenceRect.setPosition(sprite.getPosition().x + 768, sprite.getPosition().y + 106);
	defenceRect.setFillColor(Color::Blue);

	items[0].rect.left = 540;
	items[0].rect.top = 320;

	items[1].rect.left = 640;
	items[1].rect.top = 320;
	/*for (int i = 0; i < 8; i++) {
		items[i].rect.setSize(Vector2f(64,64));
		if (i % 2 == 0) {
			items[i].rect.setPosition(540,  320);
		}
	}*/
}

void Inventory::addItem(Consumable &item) {
	for (int i = 0; i < 8; i++) {
		if (items[i].isEmpty) {
			item.rect.left = items[i].rect.left;
			item.rect.top = items[i].rect.top;
			item.spriteInInventory.setPosition(item.rect.left,item.rect.top);
			item.isEmpty = false;
			items[i] = item;
			break;
		}
	}
}

void Inventory::addItem(Equipment item) {

}