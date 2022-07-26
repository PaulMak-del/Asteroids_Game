#include <iostream>
#include "Game.h"
#include "Ship.h"
#include "Asteroid.h"
#include "AstManagement.h"

#define DEBUG

Game::Game(unsigned int width, unsigned int height) 
    : _window(sf::VideoMode({ width, height}), "Asteroids!") {
#ifdef DEBUG
    std::cout << "Constructor: Game(unsigned int width, unsigned int height)\n";
#endif
    state = MENU;
    _window.setVerticalSyncEnabled(true);
}

Game::~Game() {
#ifdef DEBUG
    std::cout << "Destructor: ~Game()\n";
#endif
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
    Ship ship;
    ship.setPosition(sf::Vector2f(_window.getPosition().x / 2.0f, _window.getPosition().y / 2.0f));

    std::vector<Asteroid*> ast;
    AstManagement astManager = AstManagement();
    ast.push_back(astManager.create(LARGE));
    ast.push_back(astManager.create(MEDIUM));
    ast.push_back(astManager.create(SMALL));

    ast[0]->setPosition(sf::Vector2f(400, 400));
    ast[1]->setPosition(sf::Vector2f(500, 500));
    ast[2]->setPosition(sf::Vector2f(600, 600));
    //======================

    while (_window.isOpen())
    {
        //Поведение игры
        //ПОВОРОТ КОРАБЛЯ
        sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
        sf::Vector2f shipPos = ship.getPosition();
        sf::Vector2f dir = (sf::Vector2f(float(mousePos.x - shipPos.x), float(mousePos.y - shipPos.y))).normalized();
        sf::Angle angle = dir.angleTo(sf::Vector2f(1.f, 0.f));

        ship.setRotation(-angle);
        //"БЕСКОНЕЧНОЕ" ПОЛЕ
        //для коробля
        ship.setPosition(sf::Vector2f(float(int(shipPos.x) % _window.getSize().x), float(int(shipPos.y) % _window.getSize().y)));
        if (shipPos.x < 0) {
            ship.setPosition(sf::Vector2f(float(_window.getSize().x), shipPos.y));
        }
        if (shipPos.y < 0) {
            ship.setPosition(sf::Vector2f(shipPos.x, float(_window.getSize().y)));
        }

        //для астероидов (выглядит ужасно, потом перелаешь)
        const float magicOffset = 5;
        for (int i = 0; i < ast.size(); ++i) {
            Asteroid* el = ast[i];
            if (el->getPosition().x < 0 - el->getScale().x * magicOffset) {
                el->setPosition(sf::Vector2f(float(_window.getSize().x + el->getScale().x * magicOffset), el->getPosition().y));
            }
            if (el->getPosition().y < 0 - el->getScale().x * magicOffset) {
                el->setPosition(sf::Vector2f(el->getPosition().x, float(_window.getSize().y + el->getScale().x * magicOffset)));
            }
            if (el->getPosition().x > _window.getSize().x + el->getScale().x * magicOffset ) {
                el->setPosition(sf::Vector2f(float(el->getScale().x * -magicOffset ), el->getPosition().y));
            }
            if (el->getPosition().y > _window.getSize().y + el->getScale().x * magicOffset ) {
                el->setPosition(sf::Vector2f(el->getPosition().x, float(el->getScale().x * -magicOffset )));
            }
        }
        //ПОЛЁТ АСТЕРОИДОВ
        for (auto el : ast) {
            el->move();
        }

        //РАЗРУШЕНИЕ АСТЕРОИДОВ
        
        //===========================

        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                _window.close();
                state = GAME_OVER;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            _window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            ship.move(dir);
        }


        _window.clear();
        _window.draw(ship);
        for (int i = 0; i < ast.size(); ++i) {
            _window.draw(*ast[i]);
        }
        _window.display();
    }
    for (int i = 0; i < ast.size(); ++i) {
        delete ast[i];
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
    return _window.isOpen();
}
