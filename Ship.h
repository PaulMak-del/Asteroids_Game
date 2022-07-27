#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

struct Bullet {
	sf::CircleShape bul;
	sf::Vector2f dir;
	Bullet();
	Bullet(const sf::CircleShape&, const sf::Vector2f&);
	~Bullet();
};

class Ship : public sf::Drawable, public sf::Transformable
{
private:
	sf::ConvexShape _ship;
	float _speed;
	float _size;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;
public:
	Ship();
	void move(sf::Vector2f dir);
	Bullet* shoot(sf::Vector2f dir);
};

