#include "Asteroid.h"
#include <iostream>

static const int POINT_AMOUNT = 6;

Asteroid::Asteroid(AST_SIZE size) : _ast(POINT_AMOUNT) {
	std::cout << "Asteroid()\n";

	generate();
	this->scale(sf::Vector2f(float(size), float(size)));
}

void Asteroid::generate() {
	_ast.setPoint(0, sf::Vector2f(0.f, 0.f));

	float x = float(rand() % 3 - 5);
	float y = -x * 0.5f;
	_ast.setPoint(1, sf::Vector2f(x, y));

	x = float(rand() % 5 - 5);
	y = -x * 2;
	_ast.setPoint(2, sf::Vector2f(x, y));

	x = 0;
	y = float(rand() % 3 + 7);
	_ast.setPoint(3, sf::Vector2f(x, y));

	x = float(rand() % 3 + 2);
	y = x * 2;
	_ast.setPoint(4, sf::Vector2f(x, y));

	x = float(rand() % 3 + 2);
	y = x * 0.5f;
	_ast.setPoint(5, sf::Vector2f(x, y));
}

Asteroid::~Asteroid() {
	std::cout << "~Asteroid()\n";
}

void Asteroid::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	sf::RenderStates statesCopy(states);
	statesCopy.transform *= getTransform();
	target.draw(_ast, statesCopy);
}

