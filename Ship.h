#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Ship 
{
private:
	sf::ConvexShape _ship;
	float _speed;
	float _size;
public:
	Ship();
	void move(sf::Vector2f dir);
	void setPosition(sf::Vector2f vec);
	sf::Vector2f getPosition();
	void setRotation(sf::Angle angle);
	sf::ConvexShape* getDrawable();
};


