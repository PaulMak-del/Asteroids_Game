#include <iostream>
#include "Game.h"

#define DEBUG

Game::Game(unsigned int width, unsigned int height) 
    : _window(sf::VideoMode({ width, height}), "Asteroids!")
{
    state = MENU;

    //Window
    _window.setVerticalSyncEnabled(true);

	//Ship stuff
    ship.setPosition(sf::Vector2f(_window.getPosition().x / 2.0f, _window.getPosition().y / 2.0f));

	//HP Bar
    for (int i = 0; i < ship.getHP(); ++i) {
        hpBar.push_back(sf::RectangleShape());
        hpBar[i].setSize(sf::Vector2f(60.f, 25.f));
        hpBar[i].setFillColor(sf::Color::White);
        hpBar[i].setPosition(sf::Vector2f(20.f + i * 63.f, 20.f));
    }

	//Asteroid stuff
    ast.push_back(astManager.create(LARGE));
    ast.push_back(astManager.create(LARGE));
    ast.push_back(astManager.create(LARGE));

    ast[0]->setPosition(sf::Vector2f(400, 400));
    ast[1]->setPosition(sf::Vector2f(500, 500));
    ast[2]->setPosition(sf::Vector2f(600, 600));
}

Game::~Game() {
	//Asteroid stuff
    for (int i = 0; i < ast.size(); ++i) {
        delete ast[i];
    }
}

void Game::menu() {
    std::cout << "MENU\n";

    sf::Font font;
    if (!font.loadFromFile("font.ttf")) {
        throw 12;
    }
    sf::Text enter;
    enter.setFont(font);
    enter.setString("Press Enter to Start");
    enter.setFillColor(sf::Color::White);
    enter.setCharacterSize(30);
    enter.setOrigin(sf::Vector2f(enter.getGlobalBounds().width / 2,
                                       enter.getGlobalBounds().height / 2));
    enter.setPosition(sf::Vector2f(static_cast<float>(_window.getSize().x * 0.5f),
                                          static_cast<float>(_window.getSize().y * 0.3f)));

    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                _window.close();
                state = GAME_OVER;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            break;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            _window.close();
        }

        _window.clear();
        _window.draw(enter);
        _window.display();
    }

    state = GAME_RUNING;
}

void Game::game_run()
{
    std::cout << "GAME_RUNING\n";

    while (state == GAME_RUNING) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;

    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) {
            _window.close();
            state = GAME_OVER;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { //Завершение игры
        state = MENU;
        //_window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { //Движение корабля
        ship.setForceDirection(ship.getDirection());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { //Создание снаряда
        ship.addBullet();
    }
}

void Game::update() 
{
    ship.update(_window);

    for (auto el : ast) {
        el->update(_window);
    }

    ship.bulletUpdate(_window);

    //ПРОВЕРКА КОЛЛИЗИЙ
    //Проверка коллизий между снарядами и астероидами
    for (int i = 0; i < ship.bullets.size(); ++i) {
        for (int j = 0; j < ast.size() && i < ship.bullets.size(); ++j) {
            if (ast[j]->getGlobalBounds().findIntersection(ship.bullets[i]->getGlobalBounds())) {
                delete ship.bullets[i];
                ship.bullets.erase(ship.bullets.begin() + i);
                if (i > 0) {
                    i--;
                }

                if (ast[j]->getSize() == LARGE) {
                    ast.push_back(astManager.create(MEDIUM));
                    ast.back()->setPosition(ast[j]->getPosition());
                    ast.push_back(astManager.create(MEDIUM));
                    ast.back()->setPosition(ast[j]->getPosition());
                }
                else if (ast[j]->getSize() == MEDIUM) {
                    ast.push_back(astManager.create(SMALL));
                    ast.back()->setPosition(ast[j]->getPosition());
                    ast.push_back(astManager.create(SMALL));
                    ast.back()->setPosition(ast[j]->getPosition());
                }

                delete ast[j];
                ast.erase(ast.begin() + j);
                j--;
                
            }
        }
    }

    //Проверка коллизий между кораблём и астероидами
    for (int i = 0; i < ast.size(); ++i) {
        if (ship.getGlobalBounds().findIntersection(ast[i]->getGlobalBounds())) {
            std::cout << "true ";
            if (ship.getLastDamageTime() > 100) {
                ship.damage();
            }
        }
    }
}

void Game::render() {
    _window.clear();
    for (auto bullet : ship.bullets) {
        _window.draw(bullet->bul);
    }
    _window.draw(ship);
    for (int i = 0; i < ast.size(); ++i) {
        _window.draw(*ast[i]);
    }
    for (int i = 0; i < ship.getHP(); ++i) {
        _window.draw(hpBar[i]);
    }
    _window.display();
}

void Game::game_over()
{
#ifndef DEBUG
    std::cout << "GAME_OVER\n";
#endif
}

void Game::pause()
{
#ifdef DEBUG
    std::cout << "PAUSE\n";
#endif
}

void Game::restart()
{
#ifdef DEBUG
    std::cout << "RESTART\n";
#endif
}

bool Game::isRuning() 
{
    return _window.isOpen();
}

