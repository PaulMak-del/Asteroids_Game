#include "Asteroid.h"
#include <iostream>

static const int POINT_AMOUNT = 6;

Asteroid::Asteroid(AST_SIZE size) : _ast(POINT_AMOUNT), _size(size) {
	if (_size == LARGE) {
		_speed = 2;
	}
	else if (_size == MEDIUM) {
		_speed = 3;
	}
	else {
		_speed = 4;
	}
	_dir.x = float(rand() - RAND_MAX / 2);
	_dir.y = float(rand() - RAND_MAX / 2);
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

Asteroid::~Asteroid() {}

void Asteroid::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
	sf::RenderStates statesCopy(states);
	statesCopy.transform = getTransform();
	target.draw(_ast, statesCopy);
}

void Asteroid::update(sf::RenderWindow& window) {
	const float magicOffset = 5;
    if (_ast.getPosition().x < 0 - _ast.getScale().x * magicOffset) {
        _ast.setPosition(sf::Vector2f(float(window.getSize().x + _ast.getScale().x * magicOffset), _ast.getPosition().y));
    }
    if (_ast.getPosition().y < 0 - _ast.getScale().x * magicOffset) {
        _ast.setPosition(sf::Vector2f(_ast.getPosition().x, float(window.getSize().y + _ast.getScale().x * magicOffset)));
    }
    if (_ast.getPosition().x > window.getSize().x + _ast.getScale().x * magicOffset ) {
        _ast.setPosition(sf::Vector2f(float(_ast.getScale().x * -magicOffset ), _ast.getPosition().y));
    }
    if (_ast.getPosition().y > window.getSize().y + _ast.getScale().x * magicOffset ) {
        _ast.setPosition(sf::Vector2f(_ast.getPosition().x, float(_ast.getScale().x * -magicOffset )));
    }

    _ast.move(_dir * _speed);
}

sf::Vector2f Asteroid::getPosition() {
	return _ast.getPosition();
}

void Asteroid::setPosition(sf::Vector2f vec) {
	_ast.setPosition(vec);
}

sf::FloatRect Asteroid::getGlobalBounds() {
	return _ast.getGlobalBounds();
}

AST_SIZE Asteroid::getSize() {
	return _size;
}







