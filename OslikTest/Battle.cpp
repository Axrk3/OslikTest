#include "Battle.h"

Battle::Battle(Player &_player, Enemy *&_enemy, int _enemyAmount) {
	player = _player;
	enemy = _enemy;

	enemyAmount = _enemyAmount;
	deadEnemy = 0;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;
}

int Battle::battleEnd(RenderWindow &window) {
	Texture endTexture;
	Sprite endSprite;

	if (!player.isAlive() || deadEnemy == enemyAmount) {
		if (!player.isAlive())
			endTexture.loadFromFile("ded.png");
		else 
			endTexture.loadFromFile("win.png");

		endSprite.setTexture(endTexture);
		endSprite.setPosition(11 * resolution.x / 24, 9 * resolution.y / 27);

		do 
		{
			window.clear(Color::White);
			window.draw(endSprite);
			window.display();
			sleep(seconds(0.1f));
		} while (!Keyboard::isKeyPressed(Keyboard::Enter));

		if (!player.isAlive())
			return 0;
		else
			return 1;
	}

	return 2;
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
	player.sprite.setPosition(resolution.x / 8, resolution.y / 4);
	for (int i = 0; i < enemyAmount; i++)
		enemy[i].sprite.setPosition((i + 5) * resolution.x / 8, (i + 1) * resolution.y / 8);

	Vector2f outlineHPSize;
	outlineHPSize.y = resolution.y / 64;

	hpBar.setFillColor(Color::Red);
	outlineHP.setOutlineThickness(1);
	outlineHP.setOutlineColor(Color::Black);
	outlineHP.setFillColor(Color::Transparent);
	
	hpBar.setPosition(player.sprite.getPosition().x, player.sprite.getPosition().y - resolution.y / 16);
	outlineHP.setPosition(player.sprite.getPosition().x, player.sprite.getPosition().y - resolution.y / 16);
	outlineHPSize.x = player.stats.HP;
	outlineHP.setSize(outlineHPSize);
}

void Battle::drawElements(RenderWindow &window) {
	window.clear(Color::White);
	
	window.draw(player.getSprite());
	for (int i = 0; i < enemyAmount; i++)
		if (enemy[i].isAlive())
			window.draw(enemy[i].getSprite());

	Vector2f hpBarSize;
	hpBarSize.y = resolution.y / 64;
	hpBarSize.x = player.stats.HP;
	hpBar.setSize(hpBarSize);

	window.draw(hpBar);
	window.draw(outlineHP);

	window.draw(menu);
	for (int i = 0; i < 4; i++) {
		window.draw(menuBar[i]);
		window.draw(text[i]);
	}

	window.draw(cursor);
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

void Battle::defenceDown(Character &defender) {
	defender.stats.DEF -= 10;
}

void Battle::attack(Character &attacker, Character &defender, int speed, RenderWindow &window) {
	Vector2f offset;
	offset.x = speed * 0.05;
	offset.y = 0;
	int step = 0;

	while (attacker.sprite.getPosition().x != defender.sprite.getPosition().x) {
		attacker.sprite.move(offset);

		step++;

		drawElements(window);
		window.display();
	}

	defender.stats.HP -= attacker.stats.ATK / defender.stats.DEF;
	if (!defender.isAlive())
		deadEnemy++;

	while (step) {
		attacker.sprite.move(-offset);
		step--;

		drawElements(window);
		window.display();
	}
}

int Battle::chooseEnemy(RenderWindow &window) {
	int choice;
	for (int i = 0; i < enemyAmount; i++)
		if (enemy[i].isAlive()) {
			choice = i;
			break;
		}
	cursor.setPosition(enemy[choice].sprite.getPosition());

	do {
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if (choice != 0) {
				choice--;
				if (enemy[choice].isAlive())
					cursor.setPosition(enemy[choice].sprite.getPosition());
			}

		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			if (choice != enemyAmount - 1) {
				choice++;
				if (enemy[choice].isAlive())
					cursor.setPosition(enemy[choice].sprite.getPosition());
			}
		}

		drawElements(window);
		window.display();
		sleep(seconds(0.1f));
	} while (!Keyboard::isKeyPressed(Keyboard::Enter));
		

	return choice;
}

void Battle::actionProcessing(RenderWindow &window) {
	int choice;

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		switch (action) {
		case 1:
			choice = chooseEnemy(window);
			attack(player, enemy[choice], 20, window);
			isAction = true;
			break;
		case 2:
			defenceUp(player);
			isAction = true;
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

	while (true) {
		sleep(seconds(0.1f));

		drawElements(window);

		cursor.setPosition(currentPosition);

		input();
		actionProcessing(window);

		cursor.setPosition(currentPosition);

		if (isAction) {
			for (int i = 0; i < enemyAmount; i++) {
				if (enemy[i].isAlive())
					attack(enemy[i], player, -20, window);
			}
			isAction = false;
		}
			
		if (isBlocked) {
			defenceDown(player);
			isAction = false;
			isBlocked = false;
		}
		window.display();

		switch (battleEnd(window))
		{
		case 0: 
			exit(0);
		case 1: 
			return;
		default:
			break;
		}
	}
}