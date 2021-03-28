#include "Battle.h"

Battle::Battle(Player &_player, Enemy &_enemy) {
	player = _player;
	enemy = _enemy;
}

void Battle::StartBattle(RenderWindow &window) {
	Font font;
	Text text;

	player.sprite.setPosition(VideoMode::getDesktopMode().width / 2 - 400 , VideoMode::getDesktopMode().height / 2);
	enemy.sprite.setPosition(VideoMode::getDesktopMode().width / 2 + 400, VideoMode::getDesktopMode().height / 2);
	font.loadFromFile("times.ttf");
	text.setFont(font);


	while (player.stats.HP > 0 && enemy.stats.HP > 0) {
		window.clear(Color::White);
		
		window.draw(player.getSprite());
		window.draw(enemy.getSprite());
		

		if (Keyboard::isKeyPressed(Keyboard::F)) {
			enemy.stats.HP -= 5*player.stats.ATK;
			text.setString("You hit him!");
			text.setCharacterSize(18);
			text.setFillColor(Color::Red);
			text.setPosition(VideoMode::getDesktopMode().width / 2 + 400, VideoMode::getDesktopMode().height / 2);
			window.draw(text);
		}
		
		window.display();
		sleep(seconds(0.5f));
	}
}