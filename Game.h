#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "Ship.h"
#include "Asteroid.h"
#include "AstManagement.h"

enum GameState {
	RESTART,
	MENU,
	GAME_RUNING,
	PAUSE,
	GAME_OVER
};


class Game
{
private: 
	//---VARIABLES
	//Window
	sf::RenderWindow _window;
	
	//Ship stuff
	Ship ship;

	//HP Bar
    std::vector<sf::RectangleShape> hpBar;

	//Asteroid stuff
    std::vector<Asteroid*> ast;
    AstManagement astManager;

	//---FUNCTIONS
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





