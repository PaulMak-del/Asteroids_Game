#include <iostream>
#include "Game.h"

#define DEBUG

Game::Game(unsigned int width, unsigned int height) 
    : _window(sf::VideoMode({ width, height}), "Asteroids!"),
      hpBar(sf::Vector2f(175.f, 25.f))
{
    state = MENU;

    //Window
    _window.setVerticalSyncEnabled(true);

	//Ship stuff
    ship.setPosition(sf::Vector2f(_window.getPosition().x / 2.0f, _window.getPosition().y / 2.0f));

	//Bullet stuff

	//HP Bar
    hpBar.setFillColor(sf::Color::White);
    hpBar.setPosition(sf::Vector2f(20.f, 20.f));

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
#ifdef DEBUG
    std::cout << "MENU\n";
#endif

    while (true) {
        break;
    }

    state = GAME_RUNING;
}

void Game::game_run()
{
    std::cout << "GAME_RUNING\n";

    while (_window.isOpen()) {
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
        _window.close();
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
    //............................Изменить позже
    //Проверка коллизий между снарядами и астероидами
    for (int i = 0; i < ship.bullets.size(); ++i) {
        for (int j = 0; j < ast.size() && i < ship.bullets.size(); ++j) {
            float x = ship.bullets[i]->bul.getPosition().x;
            float y = ship.bullets[i]->bul.getPosition().y;

            Asteroid* a = ast[j];
            int ast_size = a->getSize();
            float top = a->getPosition().y - 5 * ast_size ;
            float down = a->getPosition().y + 5 * ast_size;
            float left = a->getPosition().x - 5 * ast_size;
            float right = a->getPosition().x + 5 * ast_size;
            if (x > left && x < right && y > top && y < down) {
                std::cout << "Destroy asteroid | " << a << "\n";
                delete ship.bullets[i];
                ship.bullets.erase(ship.bullets.begin() + i);
                if (i > 0) {
                    i--;
                }

                if (ast_size == LARGE) {
                    ast.push_back(astManager.create(MEDIUM));
                    ast.back()->setPosition(a->getPosition());
                    ast.push_back(astManager.create(MEDIUM));
                    ast.back()->setPosition(a->getPosition());
                }
                else if (ast_size == MEDIUM) {
                    ast.push_back(astManager.create(SMALL));
                    ast.back()->setPosition(a->getPosition());
                    ast.push_back(astManager.create(SMALL));
                    ast.back()->setPosition(a->getPosition());
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
    _window.draw(hpBar);
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

