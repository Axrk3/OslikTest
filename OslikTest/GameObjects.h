#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Level {
public:
	String* map;
	//Массивы с предметами и НПС
};

class GameObject {
protected:
	Vector2f position;
	FloatRect rect;
	Texture texture;
	Sprite sprite;
public:
	String name;
	Sprite getSprite();
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
protected:
	int ground;
	bool onGround;
	bool leftPressed;
	bool rightPressed;
	bool leftRun;
	bool rightRun;
	bool jump;
	float speed;
	float dx, dy;
	Friend friends[5];
public:
	Player();
	void moveLeft();
	void runLeft();
	void moveRight();
	void runRight();
	void Jump();
	void stopLeft();
	void stopRight();
	void update(float time);
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
