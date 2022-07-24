#pragma once

#include <SFML/Graphics.hpp>

enum AST_SIZE {
	LARGE,
	MEDIUM,
	SMALL
};

class Asteroid : public sf::Drawable, sf::Transformable
{
private:
	sf::ConvexShape _ast;

	virtual void draw(sf::RenderTarget& target, const sf::RenderStates& states) const;
public:
	Asteroid(AST_SIZE size);
	~Asteroid() override;

	void generate();
};

