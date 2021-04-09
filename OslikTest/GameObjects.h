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
public:
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
	String name;
	int maxQuantity;
public:
	Consumable();
	void consume();
	Sprite getSpriteInInventory();
};

class Inventory : public GameObject {
public:
	Consumable consum[8];
	Equipment equip[8];
	RectangleShape attackRect, hpRect;
	int quantityConsum, quantityEquip;
	
	// Сделать смещение player.sprite.setPosition(player.rect.left - offsetX, player.rect.top - offsetY);
public:
	Inventory();
	void open();
	void addItem(Consumable item, String itemName);
	void addItem(Equipment item);
};

class Character : public GameObject {
public:
	struct characteristics {
		int HP,
			//MP,
			ATK,
			DEF;
			//Level,
			//Exp,
			//initiative;
	} stats;
public:
	void fight();
	characteristics getStats();
	
};

class Friend : public Character {
	
};

class Enemy : public Character {
public:
	RectangleShape hpRect;

	Enemy();
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

