#include "Engine.h"


Engine::Engine() {
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	window.create(VideoMode(1920, 1080), "Game Engine v.1", Style::Fullscreen);

	backgroundTexture.loadFromFile("back.jpg");
	backgroundSprite.setTexture(backgroundTexture);

	regularFont.loadFromFile("times.ttf");
	regularText.setFont(regularFont);

	offsetX = offsetY = 0;

	blockSize = 64;
	rectSize.x = blockSize; rectSize.y = blockSize;
	rect.setSize(rectSize);
	lvl.changeLevel(map1);

	// Переделать в отдельную функцию(Возможно через конструктор)
	potion.name = "potion";
	potion.textureInInventory.loadFromFile("potion.png");
	potion.spriteInInventory.setTexture(potion.textureInInventory);
	player.inventory.addItem(potion);
}

void Engine::input() {
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}

	if (Keyboard::isKeyPressed(Keyboard::I)) {
		if (openInventory) openInventory = false;
		else {
			player.dx = 0; player.dy = 0;
			openInventory = true;
			openChest = false;
		}
	}
	// Если инвентарь открыт управление отключено
	if (!openInventory) {

		if (Keyboard::isKeyPressed(Keyboard::A)) {
			player.dx = -300;
		}
		else {
			player.dx = 0;
		}

		if (Keyboard::isKeyPressed(Keyboard::D)) {
			player.dx = 300;
		}

		if (Keyboard::isKeyPressed(Keyboard::LShift)) player.dx *= 3;

		if (Keyboard::isKeyPressed(Keyboard::W)) {
			player.Jump();
		}
	}
}

void Engine::update(float time) {
	player.rect.left += player.dx * time;

	collision(0);

	player.dy += 1000 * time;

	player.rect.top += player.dy * time;

	collision(1);

	player.sprite.setPosition(player.rect.left - offsetX, player.rect.top - offsetY);
}

// 0 - x; 1 - y
void Engine::collision(int dir) {
	for (int i = player.getRect().top / blockSize; i < (player.getRect().top + player.getRect().height) / blockSize; i++) {
		for (int j = player.getRect().left / blockSize; j < (player.getRect().left + player.getRect().width) / blockSize; j++) {
			if ((lvl.getMap()[i][j] == 'D') || (lvl.getMap()[i][j] == 'G')) {
				if ((player.dx > 0) && (dir == 0)) player.setRect(0, j * blockSize - player.getRect().width);
				if ((player.dx < 0) && (dir == 0)) player.setRect(0, j * blockSize + blockSize);
				if ((player.dy > 0) && (dir == 1)) {
					player.setRect(1, i * blockSize - player.getRect().height);
					player.dy = 0; 
				}
				if ((player.dy < 0) && (dir == 1)) {
					player.setRect(1, i * blockSize + blockSize);
					player.dy = 0;
				}
			}
			
			if ((lvl.getMap()[i][j] == 'C' || lvl.getMap()[i][j] == 'T') && (Keyboard::isKeyPressed(Keyboard::E))) {
				if (lvl.getMap()[i][j] == 'C') {
					lvl.changeBlock(i, j);
					lvl.changeBlock(i, j + 1);
					
				} else {
					lvl.changeBlock(i, j);
					lvl.changeBlock(i, j - 1);
				}
				
				//player.inventory.addItem(player.inventory.consum[0], "potion");
				regularText.setString("You got item!!");
				regularText.setCharacterSize(32);
				regularText.setFillColor(Color::Yellow);
				regularText.setPosition((i + 4) * blockSize, (j / 4) * blockSize);
				
				prefTime = time;
				int enemyAmount = 3;
				Enemy* enemy = new Enemy[enemyAmount];
				Battle battle(player, enemy, enemyAmount);
				battle.battleStart(window);
				onFight = true;

				openChest = true;
			}
		}
	}
}

void Engine::drawMap(String map[]) {

	for (int i = 0; i < 34; i++) {
		for (int j = 0; j < 80; j++) {
			switch (map[i][j]) {
			case 'D': rect.setTexture(&lvl.dirt);
					  break;
			case 'G': rect.setTexture(&lvl.grass);
					  break;
			case 'C': rect.setTexture(&lvl.chestLeft);
					  break;
			case 'T': rect.setTexture(&lvl.chestRight);
					  break;
			default: continue;
			}
			rect.setPosition(j * blockSize - offsetX,i * blockSize - offsetY);
			window.draw(rect);
		}
	}
}

void Engine::drawInventory() {
	window.draw(player.inventory.getSprite());
	
	for (int i = 0; i < 2; i++) {
		if (!player.inventory.items[i].isEmpty) {
			window.draw(player.inventory.items[i].spriteInInventory);
		}
	}
	
	Vector2f size;
	size.x = 13 * player.stats.ATK - 2;
	size.y = 25;
	player.inventory.attackRect.setSize(size);
	window.draw(player.inventory.attackRect);
}

void Engine::draw() {
	window.clear(Color::White);
	window.draw(backgroundSprite);
	drawMap(lvl.getMap());
	window.draw(player.getSprite());
	if (openInventory) drawInventory();
	if (openChest) window.draw(regularText);
	window.display();
}

void Engine::start() {
	Clock clock;
	while (window.isOpen()) {
		Time dt = clock.restart();
		if (!onFight) {
			time = dt.asSeconds();
		}
		else {
			time = prefTime;
			onFight = false;
		}
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case Event::Closed:
				window.close();
				break;
			case Event::KeyPressed: {
				if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
				input();
				break;
			}
			case Event::KeyReleased: {
				input();
				break;
			}
			default:
				break;
			}
		}
		
		update(time);
		if (player.rect.left > resolution.x / 2 && player.rect.left < 80 * blockSize - resolution.x / 2) offsetX = player.rect.left - resolution.x / 2;
		if (player.rect.top > resolution.y / 2 && player.rect.top < 34 * blockSize - resolution.y / 2) offsetY = player.rect.top - resolution.y / 2;
		Engine::draw();
	}
}

