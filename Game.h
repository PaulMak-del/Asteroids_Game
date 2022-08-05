#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

enum GameState {
	RESTART,
	MENU,
	GAME_RUNING,
	PAUSE,
	GAME_OVER
};

const float SPEED = 5.f;

class Game
{
private: 
	sf::RenderWindow _window;

	void processEvents();
	void update();
	void render();
public:
	GameState state;

	Game(unsigned int width, unsigned int height);
	~Game();
	void restart();
	void menu();
	void game_run();
	void game_over();
	void pause();

	bool isRuning();
};





