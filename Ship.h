#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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
};

