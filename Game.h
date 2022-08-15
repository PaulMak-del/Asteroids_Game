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
	//Text stuff
	sf::Font _font;
	//Menu 
	sf::Text _menuText;
	sf::Text _menuHelpText;
	//Pause
	sf::Text _pauseText;
	sf::Text _pauseHelpText;
	sf::RectangleShape _background;
	//GameOver
	sf::Text _gameOverText;
	sf::Text _gameOverHelpText;

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
	void menuProcessEvents();
	void gameProcessEvents();
	void gameOverProcessEvents();
	void pauseProcessEvents();

	void menuUpdate();
	void gameUpdate();
	void gameOverUpdate();
	void pauseUpdate();

	void menuRender();
	void gameRender();
	void gameOverRender();
	void pauseRender();

	void menuInit();
	void gameInit();
	void pauseInit();
	void gameOverInit();
	
public:
	GameState state;

	Game(unsigned int width, unsigned int height);
	~Game();
	void game_run();
};





