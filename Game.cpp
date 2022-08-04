#include <iostream>
#include "Game.h"
#include "Ship.h"
#include "Asteroid.h"
#include "AstManagement.h"

#define DEBUG


//Вспомогательные функции
/*
bool checkCollision(sf::Transformable& ob1, sf::Transformable& ob2) {

}
*/

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

    while (true) {
        break;
    }

    state = GAME_RUNING;
}

void Game::game_run()
{
#ifdef DEBUG
    std::cout << "GAME_RUNING\n";
#endif
    //Создание объектов игры
    //Ship stuff
    Ship ship;
    ship.setPosition(sf::Vector2f(_window.getPosition().x / 2.0f, _window.getPosition().y / 2.0f));
    std::vector<Bullet*> bullets;
    const float BULLET_SPEED = 10.f;
    const long long BULLET_TIMEOUT = 10;
    long clock = 0;

    //HP Bar
    sf::RectangleShape hpBar(sf::Vector2f(175.f, 25.f));
    hpBar.setFillColor(sf::Color::White);
    hpBar.setPosition(sf::Vector2f(20.f, 20.f));

    //Asteroid stuff
    std::vector<Asteroid*> ast;
    AstManagement astManager = AstManagement();
    ast.push_back(astManager.create(LARGE));
    ast.push_back(astManager.create(LARGE));
    ast.push_back(astManager.create(LARGE));

    ast[0]->setPosition(sf::Vector2f(400, 400));
    ast[1]->setPosition(sf::Vector2f(500, 500));
    ast[2]->setPosition(sf::Vector2f(600, 600));
    //======================

    while (_window.isOpen())
    {
        //==============Поведение игры===================
        //ПОВОРОТ КОРАБЛЯ
        sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
        sf::Vector2f shipPos = ship.getPosition();
        sf::Vector2f dir = (sf::Vector2f(float(mousePos.x - shipPos.x), float(mousePos.y - shipPos.y))).normalized();
        sf::Angle angle = dir.angleTo(sf::Vector2f(1.f, 0.f));

        //ДВИЖЕНИЕ КОРОБЛЯ
        ship.update();
        ship.setRotation(-angle);

        //"БЕСКОНЕЧНОЕ" ПОЛЕ
        //для коробля
        if (shipPos.x > _window.getSize().x) {
            ship.setPosition(sf::Vector2f(0, shipPos.y));
        }
        if (shipPos.y > _window.getSize().y) {
            ship.setPosition(sf::Vector2f(shipPos.x, 0));
        }
        if (shipPos.x < 0) {
            ship.setPosition(sf::Vector2f(float(_window.getSize().x), shipPos.y));
        }
        if (shipPos.y < 0) {
            ship.setPosition(sf::Vector2f(shipPos.x, float(_window.getSize().y)));
        }

        //для астероидов (выглядит ужасно, потом перелаешь)
        const float magicOffset = 5;
        for (auto el : ast) {
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
        //ДВИЖЕНИЕ СНАРЯДОВ
        for (int i = 0; i < bullets.size(); ++i) {
            Bullet* bullet = bullets[i];
            bullet->bul.move(bullet->dir * BULLET_SPEED);
            float x = bullet->bul.getPosition().x;
            float y = bullet->bul.getPosition().y;
            if (x < 0 || x > _window.getSize().x ||
                y < 0 || y > _window.getSize().y) {
                delete bullets[i];
                bullets.erase(bullets.begin() + i);
                i--;
            }
        }

        //ПРОВЕРКА КОЛЛИЗИЙ
        for (int i = 0; i < bullets.size(); ++i) {
            for (int j = 0; j < ast.size() && i < bullets.size(); ++j) {
                float x = bullets[i]->bul.getPosition().x;
                float y = bullets[i]->bul.getPosition().y;

                Asteroid* a = ast[j];
                int ast_size = a->getSize();
                float top = a->getPosition().y - 5 * ast_size ;
                float down = a->getPosition().y + 5 * ast_size;
                float left = a->getPosition().x - 5 * ast_size ;
                float right = a->getPosition().x + 5 * ast_size ;
                if (x > left && x < right && y > top && y < down) {
                    std::cout << "Destroy asteroid | " << a << "\n";
                    delete bullets[i];
                    bullets.erase(bullets.begin() + i);
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

        for (int i = 0; i < ast.size(); ++i) {

        }
        //==============================================

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
            ship.setForceDirection(dir);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) { //Создание снаряда
            if (clock > BULLET_TIMEOUT) {
                bullets.push_back(ship.shoot(dir));
                clock = 0;
            }
        }

        if (clock < BULLET_TIMEOUT + 1) {
            clock++;
        }

        _window.clear();
        for (auto bullet : bullets) {
            _window.draw(bullet->bul);
        }
        _window.draw(ship);
        for (int i = 0; i < ast.size(); ++i) {
            _window.draw(*ast[i]);
        }
        _window.draw(hpBar);
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

