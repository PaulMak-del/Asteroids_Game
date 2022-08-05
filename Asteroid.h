#pragma once

#include <SFML/Graphics.hpp>

enum AST_SIZE {
	LARGE = 7,
	MEDIUM = 5,
	SMALL = 3
};

class Asteroid : public sf::Drawable, public sf::Transformable
{
private:
	sf::ConvexShape _ast;
	sf::Vector2f _dir;
	float _speed;
	AST_SIZE _size;

	virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;
	void generate();
public:
	Asteroid(AST_SIZE size);
	~Asteroid() override;
	void update(sf::RenderWindow& window);

	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f vec);
	sf::FloatRect getGlobalBounds();

	AST_SIZE getSize();
};

