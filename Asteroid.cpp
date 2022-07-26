#include "Asteroid.h"
#include <iostream>

static const int POINT_AMOUNT = 6;

Asteroid::Asteroid(AST_SIZE size) : _ast(POINT_AMOUNT) {
	std::cout << "Asteroid() " << this << "\n";

	_speed = float((6 - size) + 2 * (size / 7));
	_dir.x = float(rand());
	_dir.y = float(rand());
	_dir = _dir.normalized();
	generate();
	_ast.scale(sf::Vector2f(float(size), float(size)));
	_ast.setFillColor(sf::Color::Black);
	_ast.setOutlineThickness(0.5f);
	_ast.setOutlineColor(sf::Color::White);
	_ast.setOrigin(sf::Vector2f(0.f, 5.f));
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
	std::cout << "~Asteroid() " << this << "\n";
}

void Asteroid::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	sf::RenderStates statesCopy(states);
	statesCopy.transform = getTransform();
	target.draw(_ast, statesCopy);
}

void Asteroid::move() {
	this->Transformable::move(_dir * _speed);
}










