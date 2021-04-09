#include "Battle.h"

Battle::Battle(Player &_player, Enemy &_enemy) {
	player = _player;
	enemy = _enemy;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
}

void Battle::battleEnd() {
	
}

void Battle::menuInitialization() {
	Vector2f menuSize;
	menuSize.x = resolution.x / 2;
	menuSize.y = resolution.y / 4;
	menu.setFillColor(Color(100, 50, 0, 255));
	menu.setSize(menuSize);
	menu.setPosition(resolution.x / 4, 3 * resolution.y / 4);

	Vector2f barsSize;
	barsSize.x = resolution.x / 8;
	barsSize.y = resolution.y / 24;
	menuBar = new RectangleShape[4];
	for (int i = 0; i < 4; i++) {
		menuBar[i].setFillColor(Color(125, 65, 0, 255));
		menuBar[i].setSize(barsSize);

		switch (i)
		{
		case 0:
			menuBar[i].setPosition(5 * resolution.x / 16, 19 * resolution.y / 24);
			break;
		case 1:
			menuBar[i].setPosition(9 * resolution.x / 16, 19 * resolution.y / 24);
			break;
		case 2:
			menuBar[i].setPosition(5 * resolution.x / 16, 22 * resolution.y / 24);
			break;
		case 3:
			menuBar[i].setPosition(9 * resolution.x / 16, 22 * resolution.y / 24);
			break;
		default:
			break;
		}
	}
}

void Battle::textInitialization() {
	font.loadFromFile("times.ttf");
	text = new Text[4];
	for (int i = 0; i < 4; i++) {
		text[i].setFont(font);
		text[i].setCharacterSize(16);
		text[i].setFillColor(Color::Black);
		switch (i) {
		case 0:
			text[i].setString("Attack");
			text[i].setPosition(8 * resolution.x / 24, 19 * resolution.y / 24);
			break;
		case 1:
			text[i].setString("Block");
			text[i].setPosition(14 * resolution.x / 24, 19 * resolution.y / 24);
			break;
		case 2:
			text[i].setString("Inventory");
			text[i].setPosition(8 * resolution.x / 24, 22 * resolution.y / 24);
			break;
		case 3:
			text[i].setString("Exit");
			text[i].setPosition(14 * resolution.x / 24, 22 * resolution.y / 24);
			break;
		}
	}
}

void Battle::cursorInitialization() {
	Vector2f cursorSize;
	cursorSize.x = resolution.y / 24;
	cursorSize.y = resolution.y / 24;
	cursor.setFillColor(Color::Red);
	cursor.setSize(cursorSize);
	currentPosition.x = 7 * resolution.x / 24;
	currentPosition.y = 19 * resolution.y / 24;
	action = 1;
}

void Battle::unitInitialization() {
	player.sprite.setPosition(resolution.x / 4, resolution.y / 4);
	enemy.sprite.setPosition(3 * resolution.x / 4, resolution.y / 4);

	Vector2f outlineHPSize;
	outlineHPSize.y = resolution.y / 64;

	hpBar = new RectangleShape[2];
	outlineHP = new RectangleShape[2];
	for (int i = 0; i < 2; i++) {
		hpBar[i].setFillColor(Color::Red);
		outlineHP[i].setOutlineThickness(1);
		outlineHP[i].setOutlineColor(Color::Black);
		outlineHP[i].setFillColor(Color::Transparent);

		switch (i) {
		case 0:
			hpBar[i].setPosition(resolution.x / 4, 3 * resolution.y / 16);
			outlineHP[i].setPosition(resolution.x / 4, 3 * resolution.y / 16);
			outlineHPSize.x = player.stats.HP;
			outlineHP[i].setSize(outlineHPSize);
			break;
		case 1: 
			hpBar[i].setPosition(3 * resolution.x / 4, 3 * resolution.y / 16);
			outlineHP[i].setPosition(3 * resolution.x / 4, 3 * resolution.y / 16);
			outlineHPSize.x = enemy.stats.HP;
			outlineHP[i].setSize(outlineHPSize);
			break;
		}
	}

}

void Battle::drawElements(RenderWindow& window) {
	window.draw(player.getSprite());
	window.draw(enemy.getSprite());

	Vector2f hpBarSize;
	hpBarSize.y = resolution.y / 64;
	for (int i = 0; i < 2; i++){
		switch (i)
		{
		case 0:
			hpBarSize.x = player.stats.HP;
			hpBar[i].setSize(hpBarSize);
			break;
		case 1:
			hpBarSize.x = enemy.stats.HP;
			hpBar[i].setSize(hpBarSize);
			break;
		}

		window.draw(hpBar[i]);
		window.draw(outlineHP[i]);
	}

	window.draw(menu);
	for (int i = 0; i < 4; i++) {
		window.draw(menuBar[i]);
		window.draw(text[i]);
	}
}

void Battle::input() {
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		if (currentPosition.y > 19 * resolution.y / 24) {
			currentPosition.y -= 3 * resolution.y / 24;
			action -= 2;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		if (currentPosition.y < 22 * resolution.y / 24) {
			currentPosition.y += 3 * resolution.y / 24;
			action += 2;
		}	
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		if (currentPosition.x > 7 * resolution.x / 24) {
			currentPosition.x -= 6 * resolution.x / 24;
			action--;
		}	
	}

	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		if (currentPosition.x < 13 * resolution.x / 24) {
			currentPosition.x += 6 * resolution.x / 24;
			action++;
		}
	}
}

void Battle::defenceUp(Character &defender) {
	defender.stats.DEF += 10;
}

void Battle::defenceDown(Character& defender) {
	defender.stats.DEF -= 10;
}

void Battle::attack(Character &attacker, Character &defender) {
	defender.stats.HP -= attacker.stats.ATK / defender.stats.DEF;
}

void Battle::actionProcessing() {
	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		switch (action) {
		case 1:
			attack(player, enemy);
			isAttacked = true;
			break;
		case 2:
			defenceUp(player);
			isBlocked = true;
			break;
		case 3:
			
			break;
		case 4:
			exit(0);
			break;
		}
	}
}

void Battle::battleStart(RenderWindow &window) {
	
	unitInitialization();
	menuInitialization();
	textInitialization();
	cursorInitialization();

	while (player.stats.HP > 0 && enemy.stats.HP > 0) {
		sleep(seconds(0.1f));

		window.clear(Color::White);
		
		drawElements(window);
		
		cursor.setPosition(currentPosition);

		input();
		actionProcessing();

		if (isAttacked) {
			attack(enemy, player);
			isAttacked = false;
		}

		if (isBlocked) {
			attack(enemy, player);
			defenceDown(player);
			isBlocked = false;
		}

		window.draw(cursor);
		window.display();
	}
}