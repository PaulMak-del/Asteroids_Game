#include <iostream>
#include "Ship.h"

#define DEBUG

const float MAX_SPEED = 7.f;
const float DELTA_SPEED = 0.2f;

void Ship::draw(sf::RenderTarget& target, const sf::RenderStates& states) const
{
    sf::RenderStates statesCopy(states);
    statesCopy.transform *= getTransform();
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

sf::Vector2f Ship::getDirection() {
    return _dir;
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

sf::Vector2f Ship::getPosition() {
    return _ship.getPosition();
}

void Ship::setPosition(sf::Vector2f vec) {
    _ship.setPosition(vec);
}
void Ship::setPosition(float x, float y) {
    _ship.setPosition(sf::Vector2f(x, y));
}

void Ship::setRotation(sf::Angle angle) {
    _ship.setRotation(angle);
}

void Ship::update(sf::RenderWindow& _window) {
    //Поворот и движение 
    sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
    sf::Vector2f shipPos = _ship.getPosition();
    _dir = (sf::Vector2f(float(mousePos.x - shipPos.x), float(mousePos.y - shipPos.y))).normalized();
    sf::Angle angle = _dir.angleTo(sf::Vector2f(1.f, 0.f));
    _ship.setRotation(-angle);
    _ship.sf::Transformable::move(sf::Vector2f(_speedX, _speedY));

    //Бесконечное поле
    if (shipPos.x > _window.getSize().x) {
        _ship.setPosition(sf::Vector2f(0, shipPos.y));
    }
    if (shipPos.y > _window.getSize().y) {
        _ship.setPosition(sf::Vector2f(shipPos.x, 0));
    }
    if (shipPos.x < 0) {
        _ship.setPosition(sf::Vector2f(float(_window.getSize().x), shipPos.y));
    }
    if (shipPos.y < 0) {
        _ship.setPosition(sf::Vector2f(shipPos.x, float(_window.getSize().y)));
    }

    //Частота стрельбы
    if (_timeSinceLastShoot < BULLET_TIMEOUT) {
        _timeSinceLastShoot++;
    }
    if (_timeSinceLastDamage < 1000) {
        _timeSinceLastDamage++;
    }
}

sf::FloatRect Ship::getGlobalBounds() {
    return _ship.getGlobalBounds();
}

Ship::Bullet* Ship::shoot(sf::Vector2f dir) {
    float radius = 2.f;
    sf::CircleShape ret(radius);
    ret.setOrigin(sf::Vector2f(radius / 2, radius / 2));
    ret.setPosition(_ship.getPosition());

    return new Bullet(ret, dir);
}

void Ship::addBullet() {
        if (_timeSinceLastShoot >= BULLET_TIMEOUT) {
            bullets.push_back(shoot(_dir));
            _timeSinceLastShoot = 0;
        }
}

void Ship::bulletUpdate(sf::RenderWindow& window) {
    //Движение снарядов
    for (int i = 0; i < bullets.size(); ++i) {
        Ship::Bullet* bullet = bullets[i];
        bullet->bul.move(bullet->dir * BULLET_SPEED);
        float x = bullet->bul.getPosition().x;
        float y = bullet->bul.getPosition().y;
        if (x < 0 || x > window.getSize().x ||
            y < 0 || y > window.getSize().y) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }
}

sf::FloatRect Ship::Bullet::getGlobalBounds() {
    return bul.getGlobalBounds();
}

long Ship::getLastDamageTime() {
    return _timeSinceLastDamage;
}

void Ship::damage() {
    std::cout << "Ouch!\n";
    _timeSinceLastDamage = 0;
    _hp--;
    if (_hp <= 0) {
        std::cout << "DEAD\n";
    }
}

int Ship::getHP() {
    return _hp;
}
