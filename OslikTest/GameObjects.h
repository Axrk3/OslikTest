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

class Character : public GameObject {
protected:
	struct characteristics {
		int HP,
			MP,
			ATK,
			DEF,
			Level,
			Exp,
			initiative;
	};
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
	Friend friends[5];
public:
	Player();
	float dx, dy;
	bool onGround;
	void Jump();
};

class Item : public GameObject {
	int quantity;
	Texture textureInInventory;
	Sprite spriteInInventory;
};


class Equipment : public Item {
	void putOn();
};

class Consumable : public Item {
public:
	void consume();
	int maxQuantity;
};

class Inventory {
protected:
	Consumable consum[8];
	Equipment equip[8];
public:
	void show();
	void addItem(Consumable item);
	void addItem(Equipment item);

};
