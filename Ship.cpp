#include <iostream>
#include "Ship.h"

#define DEBUG

const float MAX_SPEED = 7.f;
const float DELTA_SPEED = 0.2f;

Bullet::Bullet(const sf::CircleShape& shape, const sf::Vector2f& direction) 
    : bul(shape), dir(direction) {
}

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

    _speedX = 0;
    _speedY = 0;
    _dir = sf::Vector2f(0.f, 0.f);
    _hp = 3;
}

void Ship::setForceDirection(sf::Vector2f dir) {
    _dir = dir;

    if (_speedX <= MAX_SPEED && _speedX >= -MAX_SPEED) {
        _speedX += DELTA_SPEED * _dir.x;
    }
    else if (_speedX < 0) {
        _speedX = -MAX_SPEED;
    }
    else {
        _speedX = MAX_SPEED;
    }

    if (_speedY <= MAX_SPEED && _speedY >= -MAX_SPEED) {
        _speedY += DELTA_SPEED  * _dir.y;
    }
    else if (_speedY < 0) {
        _speedY = -MAX_SPEED;
    }
    else {
        _speedY = MAX_SPEED;
    }

}

void Ship::update() {
    this->sf::Transformable::move(sf::Vector2f(_speedX, 0.f));
    this->sf::Transformable::move(sf::Vector2f(0.f, _speedY));
}

sf::FloatRect Ship::getGlobalBounds() {
    return _ship.getGlobalBounds();
}

Bullet* Ship::shoot(sf::Vector2f dir) {
    float radius = 2.f;
    sf::CircleShape ret(radius);
    ret.setOrigin(sf::Vector2f(radius / 2, radius / 2));
    ret.setPosition(this->getPosition());

    return new Bullet(ret, dir);
}
