#include <iostream>
#include "Game.h"
#include "Ship.h"
#include "Asteroid.h"

#define DEBUG

Game::Game(unsigned int width, unsigned int height) {
#ifdef DEBUG
    std::cout << "Constructor: Game(unsigned int width, unsigned int height)\n";
#endif
    state = MENU;
	_window = new sf::RenderWindow(sf::VideoMode({ width, height}), "Asteroids!");
    _window->setVerticalSyncEnabled(true);
}

Game::~Game() {
#ifdef DEBUG
    std::cout << "Destructor: ~Game()\n";
#endif
	delete _window;
}

void Game::menu() {
#ifdef DEBUG
    std::cout << "MENU\n";
#endif
}

void Game::game_run()
{
#ifdef DEBUG
    std::cout << "GAME_RUNING\n";
#endif
    //Создание объектов игры
    Ship* ship = new Ship();
    ship->setPosition(sf::Vector2f(_window->getPosition().x / 2.0f, _window->getPosition().y / 2.0f));

    int AST_AMOUNT = 4;
    std::vector<Asteroid*> ast;
    for (int i = 0; i < AST_AMOUNT; ++i) {
        ast.push_back(new Asteroid(LARGE));
        ast[i]->setPosition(sf::Vector2f(float(100 * (i + 1)), float(100 * (i + 1))));
    }
    //======================

    while (_window->isOpen())
    {
        //Поведение игры
        //ПОВОРОТ КОРАБЛЯ
        sf::Vector2i mousePos = sf::Mouse::getPosition(*_window);
        sf::Vector2f shipPos = ship->getPosition();
        sf::Vector2f dir = (sf::Vector2f(float(mousePos.x - shipPos.x), float(mousePos.y - shipPos.y))).normalized();
        sf::Angle angle = dir.angleTo(sf::Vector2f(1.f, 0.f));

        ship->setRotation(-angle);
        //"БЕСКОНЕЧНОЕ" ПОЛЕ
        //для коробля
        ship->setPosition(sf::Vector2f(float(int(shipPos.x) % _window->getSize().x), float(int(shipPos.y) % _window->getSize().y)));
        if (shipPos.x < 0) {
            ship->setPosition(sf::Vector2f(float(_window->getSize().x), shipPos.y));
        }
        if (shipPos.y < 0) {
            ship->setPosition(sf::Vector2f(shipPos.x, float(_window->getSize().y)));
        }
        //для астероидов (выглядит ужасно, потом перелаешь)
        const float magicOffset = 5;
        for (auto el : ast) {
            if (el->getPosition().x < 0 - el->getSize() * magicOffset ) {
                el->setPosition(sf::Vector2f(float(_window->getSize().x + el->getSize() * magicOffset), el->getPosition().y));
            }
            if (el->getPosition().y < 0 - el->getSize() * magicOffset) {
                el->setPosition(sf::Vector2f(el->getPosition().x, float(_window->getSize().y + el->getSize() * magicOffset)));
            }
            if (el->getPosition().x > _window->getSize().x + el->getSize() * magicOffset ) {
                el->setPosition(sf::Vector2f(float(el->getSize() * -magicOffset ), el->getPosition().y));
            }
            if (el->getPosition().y > _window->getSize().y + el->getSize() * magicOffset ) {
                el->setPosition(sf::Vector2f(el->getPosition().x, float(el->getSize() * -magicOffset )));
            }
        }
        //ПОЛЁТ АСТЕРОИДОВ
        for (auto el : ast) {
            el->move();
        }
        //===========================

        sf::Event event;
        while (_window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                _window->close();
                state = GAME_OVER;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            _window->close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            ship->move(dir); 
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            ast[0]->destroy();
            //Добавить новые астероиды в массив. 
            //Для этого заменить массив на вектор и обновить очистку ресурсов.
        }


        _window->clear();
        _window->draw( *(ship->getDrawable()) );
        for (auto el : ast) {
            _window->draw(el->getDrawable());
        }
        _window->display();
    }
    //Освобождение ресурсов
    delete ship;
    for (auto el : ast) {
        delete el;
    }
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
    return _window->isOpen();
}

