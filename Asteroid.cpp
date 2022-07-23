#include "Asteroid.h"
#include <vector>
#include <iostream>

Asteroid::Asteroid(AST_SIZE size) {
	if (size == NONE) {
		std::cout << "ASTEROID SIZE ERROR\n";
	}
	_size = size;
	if (size == LARGE) {
		_speed = 1;
	}
	else if (size == MEDIUM) {
		_speed = 2;
	}
	else {
		_speed = SMALL;
	}
	_points = 6;
	_asteroid.setFillColor(sf::Color::Black);
	_asteroid.setOutlineThickness(0.6f);
	_asteroid.setOrigin(sf::Vector2f(0.f, 5.f));
	_dir = sf::Vector2f(float(rand()), float(rand())).normalized();
	generate();
}

void Asteroid::generate() {
	_asteroid.setPointCount(_points);
	_asteroid.setPoint(0, sf::Vector2(0.f, 0.f));
	float x = float(rand() % 3 - 5);
	float y = -x * 0.5f;
	_asteroid.setPoint(1, sf::Vector2(x, y));
	x = float(rand() % 5 - 5);
	y = -x * 2;
	_asteroid.setPoint(2, sf::Vector2(x, y));
	x = 0;
	y = float(rand() % 3 + 7);
	_asteroid.setPoint(3, sf::Vector2(x, y));
	x = float(rand() % 3 + 2);
	y = x * 2;
	_asteroid.setPoint(4, sf::Vector2(x, y));
	x = float(rand() % 3 + 2);
	y = x * 0.5f;
	_asteroid.setPoint(5, sf::Vector2(x, y));

	_asteroid.scale(sf::Vector2f(float(_size), float(_size)));
}

sf::ConvexShape Asteroid::getDrawable() {
	return _asteroid;
}

void Asteroid::setPosition(sf::Vector2f vec) {
	_asteroid.setPosition(vec);
}

sf::Vector2f Asteroid::getPosition() {
	return _asteroid.getPosition();
}

//Возвращает размер астероидов, которые нужно создать 
//после его уничтожения
//NONE -- не создавать астероиды
AST_SIZE Asteroid::destroy() {
#ifndef DEBUG
	std::cout << "DESTOY!\n";
#endif
	return AST_SIZE((_size + 1) / 2);
}

void Asteroid::setSize(AST_SIZE size) {
	_size = size;
}

AST_SIZE Asteroid::getSize() {
	return _size;
}
void Asteroid::move() {
	_asteroid.move(_dir * _speed);
}








