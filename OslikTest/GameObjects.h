#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class GameObject {
public:
	Vector2f position;
	FloatRect rect;
	Texture texture;
	Sprite sprite;
public:
	String name;
	Sprite getSprite();
	void setRect(int id, int value);
	FloatRect getRect();
};

class Item : public GameObject {
	int quantity;
	Texture textureInInventory;
	Sprite spriteInInventory;
};


class Equipment : public Item {
public:
	void putOn();
};

class Consumable : public Item {
public:
	void consume();
	int maxQuantity;
};

class Inventory {
public:
	Consumable consum[8];
	Equipment equip[8];
	int quantityConsum, quantityEquip;
	RectangleShape rect;
	Vector2f scale;
	// Сделать смещение player.sprite.setPosition(player.rect.left - offsetX, player.rect.top - offsetY);
public:
	Inventory();
	void open();
	void addItem(Consumable item);
	void addItem(Equipment item);
};

class Character : public GameObject {
public:
	struct characteristics {
		int HP,
			MP,
			ATK,
			DEF,
			Level,
			Exp,
			initiative;
	}characteristics;
public:
	void fight();
	void getStats();
};

class Friend : public Character {
	
};

class Enemy : public Character {
	void drop();
};

class Player : public Character {
public:
	int ground;
	bool jump;
	Inventory inventory;
public:
	Player();
	float dx, dy;
	void Jump();
};

