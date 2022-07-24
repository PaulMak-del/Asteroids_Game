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





