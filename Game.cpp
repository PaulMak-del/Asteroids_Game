#include <iostream>
#include "Game.h"
#include "Ship.h"
#include "Asteroid.h"

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
    //—ÓÁ‰‡ÌËÂ Ó·˙ÂÍÚÓ‚ Ë„˚
    Ship ship;
    ship.setPosition(sf::Vector2f(_window.getPosition().x / 2.0f, _window.getPosition().y / 2.0f));
    //======================

    while (_window.isOpen())
    {
        //œÓ‚Â‰ÂÌËÂ Ë„˚
        //œŒ¬Œ–Œ“  Œ–¿¡Àﬂ
        sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
        sf::Vector2f shipPos = ship.getPosition();
        sf::Vector2f dir = (sf::Vector2f(float(mousePos.x - shipPos.x), float(mousePos.y - shipPos.y))).normalized();
        sf::Angle angle = dir.angleTo(sf::Vector2f(1.f, 0.f));

        ship.setRotation(-angle);
        //"¡≈— ŒÕ≈◊ÕŒ≈" œŒÀ≈
        //‰Îˇ ÍÓÓ·Îˇ
        ship.setPosition(sf::Vector2f(float(int(shipPos.x) % _window.getSize().x), float(int(shipPos.y) % _window.getSize().y)));
        if (shipPos.x < 0) {
            ship.setPosition(sf::Vector2f(float(_window.getSize().x), shipPos.y));
        }
        if (shipPos.y < 0) {
            ship.setPosition(sf::Vector2f(shipPos.x, float(_window.getSize().y)));
        }
        /*
        //‰Îˇ ‡ÒÚÂÓË‰Ó‚ (‚˚„Îˇ‰ËÚ ÛÊ‡ÒÌÓ, ÔÓÚÓÏ ÔÂÂÎ‡Â¯¸)
        const float magicOffset = 5;
        for (auto el : ast) {
            if (el->getPosition().x < 0 - el->getSize() * magicOffset ) {
                el->setPosition(sf::Vector2f(float(_window.getSize().x + el->getSize() * magicOffset), el->getPosition().y));
            }
            if (el->getPosition().y < 0 - el->getSize() * magicOffset) {
                el->setPosition(sf::Vector2f(el->getPosition().x, float(_window.getSize().y + el->getSize() * magicOffset)));
            }
            if (el->getPosition().x > _window.getSize().x + el->getSize() * magicOffset ) {
                el->setPosition(sf::Vector2f(float(el->getSize() * -magicOffset ), el->getPosition().y));
            }
            if (el->getPosition().y > _window.getSize().y + el->getSize() * magicOffset ) {
                el->setPosition(sf::Vector2f(el->getPosition().x, float(el->getSize() * -magicOffset )));
            }
        }
        //œŒÀ®“ ¿—“≈–Œ»ƒŒ¬
        for (auto el : ast) {
            el->move();
        }
        */
        //–¿«–”ÿ≈Õ»≈ ¿—“≈–Œ»ƒŒ¬

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
        _window.display();
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
