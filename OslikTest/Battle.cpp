#include "Battle.h"

Battle::Battle(Player &_player, Enemy *&_enemy, int _enemyAmount) {
	player = _player;
	enemy = _enemy;

	enemyAmount = _enemyAmount;
	deadEnemy = 0;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	unitInitialization();
	menuInitialization();
	cursorInitialization();
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
	menuTexture.loadFromFile("menu.png");
	menuSprite.setTexture(menuTexture);
	menuSprite.setPosition(resolution.x / 4, 3 * resolution.y / 4);

	barSize.x = 219;
	barSize.y = 91;
	menuBar = new RectangleShape[4];
	for (int i = 0; i < 4; i++) {
		menuBar[i].setFillColor(Color::Transparent);
		menuBar[i].setSize(barSize);

		switch (i)
		{
		case 0:
			menuBar[i].setPosition(menuSprite.getPosition().x + 62, menuSprite.getPosition().y + 37);
			break;
		case 1:
			menuBar[i].setPosition(menuSprite.getPosition().x + 380, menuSprite.getPosition().y + 37);
			break;
		case 2:
			menuBar[i].setPosition(menuSprite.getPosition().x + 62, menuSprite.getPosition().y + 139);
			break;
		case 3:
			menuBar[i].setPosition(menuSprite.getPosition().x + 380, menuSprite.getPosition().y + 139);
			break;
		default:
			break;
		}
	}

	Vector2f hpBarSize;
	hpBarSize.x = 199;
	hpBarSize.y = 36;
	
	modifier = hpBarSize.x / player.stats.HP;

	outlineHP.setPosition(menuSprite.getPosition().x + 698, menuSprite.getPosition().y + 62);
	outlineHP.setSize(hpBarSize);
	outlineHP.setFillColor(Color(63, 122, 104, 255));
	outlineHP.setOutlineColor(Color(36, 72, 61, 255));
	outlineHP.setOutlineThickness(4);
	
	hpBar.setPosition(outlineHP.getPosition());
	hpBar.setSize(hpBarSize);
	hpBar.setFillColor(Color(220, 20, 60, 255));
}

void Battle::cursorInitialization() {
	cursorTexture.loadFromFile("cursor.png");
	cursorSprite.setTexture(cursorTexture);

	action.x = 0;
	action.y = 0;
	currentPosition = menuBar[(action.x + action.y)].getPosition();
}

void Battle::unitInitialization() {
	player.sprite.setPosition(resolution.x / 8, resolution.y / 4);
	for (int i = 0; i < enemyAmount; i++)
		enemy[i].sprite.setPosition((i + 5) * resolution.x / 8, (i + 1) * resolution.y / 8);
}

void Battle::drawElements(RenderWindow &window) {
	window.clear(Color::White);
	
	window.draw(player.getSprite());
	for (int i = 0; i < enemyAmount; i++)
		if (enemy[i].isAlive())
			window.draw(enemy[i].getSprite());

	Vector2f hpBarSize;
	hpBarSize.x = player.stats.HP * modifier;
	hpBarSize.y = hpBar.getSize().y;

	hpBar.setSize(hpBarSize);

	window.draw(menuSprite);
	window.draw(cursorSprite);
	window.draw(outlineHP);
	window.draw(hpBar);
}

void Battle::input() {
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		if (action.y == 1) {
			action.y--;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		if (action.y == 0) {
			action.y++;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		if (action.x == 1) {
			action.x--;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		if (action.x == 0) {
			action.x++;
		}
	}

	currentPosition.x = menuBar[(action.x + 2 * action.y)].getPosition().x + barSize.x;
	currentPosition.y = menuBar[(action.x + 2 * action.y)].getPosition().y;
}

void Battle::defenceUp(Character &defender) {
	defender.stats.DEF *= 2;
}

void Battle::defenceDown(Character &defender) {
	defender.stats.DEF /= 2;
}

void Battle::attack(Character &attacker, Character &defender, int speedX, int speedY, RenderWindow &window) {
	Vector2f offset;
	offset.x = speedX * 0.05;
	offset.y = speedY * 0.1;
	int step = 0;

	while (attacker.sprite.getPosition().x != defender.sprite.getPosition().x) {
		attacker.sprite.move(offset);
		step++;

		drawElements(window);
		window.display();
	}
	
	if (attacker.stats.ATK > defender.stats.DEF)
		defender.stats.HP -= (attacker.stats.ATK - defender.stats.DEF);

	if (!defender.isAlive()) {
		defender.stats.HP = 0;
		deadEnemy++;
	}

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

	do {
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			if (choice != 0) {
				choice--;	
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			if (choice != enemyAmount - 1) {
				choice++;
			}
		}

		if (enemy[choice].isAlive())
			cursorSprite.setPosition(enemy[choice].sprite.getPosition().x + enemy[choice].texture.getSize().x, enemy[choice].sprite.getPosition().y);

		drawElements(window);
		window.display();
		sleep(seconds(0.1f));
	} while (!Keyboard::isKeyPressed(Keyboard::Enter));
		
	return choice;
}

void Battle::actionProcessing(RenderWindow &window) {
	int choice;

	if (Keyboard::isKeyPressed(Keyboard::Enter)) {
		switch (action.x + 2 * action.y) {
		case 0:
			choice = chooseEnemy(window);
			attack(player, enemy[choice], 20, (choice == 1) ? 0 : choice ? 1 : -1, window);
			isAction = true;
			break;
		case 1:
			defenceUp(player);
			isAction = true;
			isBlocked = true;
			break;
		case 2:
			
			break;
		case 3:
			exit(0);
			break;
		}
	}
}

void Battle::battleStart(RenderWindow &window) {
	while (true) {
		sleep(seconds(0.1f));

		drawElements(window);

		cursorSprite.setPosition(currentPosition);

		input();
		actionProcessing(window);

		cursorSprite.setPosition(currentPosition);

		if (isAction) {
			for (int i = 0; i < enemyAmount; i++) {
				if (enemy[i].isAlive())
					attack(enemy[i], player, -20, (i == 1) ? 0 : i ? -1 : 1, window);
			}

			if (isBlocked) {
				defenceDown(player);
				isBlocked = false;
			}

			isAction = false;
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