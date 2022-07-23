#pragma once

#include <SFML/Graphics.hpp>

enum AST_SIZE {
	LARGE = 7,
	MEDIUM = 4,
	SMALL = 2,
	NONE = 1
};

class Asteroid
{
private:
	//Variables
	sf::ConvexShape _asteroid;
	AST_SIZE _size;
	size_t _points;
	sf::Vector2f _dir;
	float _speed;

	//Functions
	void generate();
 public:
	Asteroid(AST_SIZE size);
	AST_SIZE destroy();
	void setSize(AST_SIZE size);
	AST_SIZE getSize();
	void move();

	sf::ConvexShape getDrawable();
	void setPosition(sf::Vector2f vec);
	sf::Vector2f getPosition();
};

