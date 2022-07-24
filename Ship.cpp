#include <iostream>
#include "Ship.h"

#define DEBUG

void Ship::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
    sf::RenderStates statesCopy(states);
    statesCopy.transform = getTransform();
    target.draw(_ship, statesCopy);
}

Ship::Ship() {
    _size = 5;
    _ship.setPointCount(4);
    _ship.setOrigin(sf::Vector2f(2.5f, 2.f));
    _ship.setPoint(0, sf::Vector2f(0.0f, 0.0f));
    _ship.setPoint(1, sf::Vector2f(5.0f, 2.0f));
    _ship.setPoint(2, sf::Vector2f(0.0f, 4.0f));
    _ship.setPoint(3, sf::Vector2f(1.0f, 2.0f));
    _ship.setOutlineThickness(0.6f);
    _ship.scale(sf::Vector2f(_size, _size));
    _ship.setFillColor(sf::Color::Black);

    _speed = 5;
}
void Ship::move(sf::Vector2f dir) {
    this->sf::Transformable::move(sf::Vector2f(dir.x * _speed, dir.y * _speed));
}

