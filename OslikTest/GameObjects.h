#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

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
	bool isEmpty = true;
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

/*class Cell {
public:
	FloatRect rect;
	Item item;
	bool isEmpty = true;
};*/

class Inventory : public GameObject {
public:
	Consumable items[8];
	RectangleShape attackRect, hpRect;
	int quantityConsum, quantityEquip;
	
public:
	Inventory();
	void open();
	void addItem(Consumable &item);
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
	bool isAlive();
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

