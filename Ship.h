#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct Bullet {
	sf::CircleShape bul;
	sf::Vector2f dir;
	Bullet(const sf::CircleShape&, const sf::Vector2f&);
};

class Ship : public sf::Drawable, public sf::Transformable
{
private:
	sf::ConvexShape _ship;
	float _speedX;
	float _speedY;
	float _size;
	int _hp;
	sf::Vector2f _dir;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
public:
	Ship();
	void setForceDirection(sf::Vector2f dir);
	void update();
	sf::FloatRect getGlobalBounds();
	Bullet* shoot(sf::Vector2f dir);
};

