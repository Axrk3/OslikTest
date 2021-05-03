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
			menuBar[i].setPosition(menuSprite.getPosition().x + 64, menuSprite.getPosition().y + 36);
			break;
		case 1:
			menuBar[i].setPosition(menuSprite.getPosition().x + 412, menuSprite.getPosition().y + 36);
			break;
		case 2:
			menuBar[i].setPosition(menuSprite.getPosition().x + 64, menuSprite.getPosition().y + 140);
			break;
		case 3:
			menuBar[i].setPosition(menuSprite.getPosition().x + 412, menuSprite.getPosition().y + 140);
			break;
		default:
			break;
		}
	}
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

	window.draw(menuSprite);
	window.draw(cursorSprite);
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
	defender.stats.DEF += 10;
}

void Battle::defenceDown(Character &defender) {
	defender.stats.DEF -= 10;
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
	std::cout << step;

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
	
	unitInitialization();
	menuInitialization();
	cursorInitialization();

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