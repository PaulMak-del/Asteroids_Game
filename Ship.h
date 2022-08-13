#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Ship : public sf::Drawable, public sf::Transformable
{
private:
	struct Bullet {
		sf::CircleShape bul;
		sf::Vector2f dir;
		Bullet(const sf::CircleShape& bulShape, const sf::Vector2f& direction)
			: bul(bulShape), dir(direction) {}
		sf::FloatRect getGlobalBounds();
	};
public:
	std::vector<Bullet*> bullets;

	Ship();
	void setForceDirection(sf::Vector2f dir);
	void update(sf::RenderWindow& win);
	sf::Vector2f getDirection();
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f vec);
	void setPosition(float x, float y);
	void setRotation(sf::Angle angle);
	Bullet* shoot(sf::Vector2f dir);
	void addBullet();
	void bulletUpdate(sf::RenderWindow& window);
	long getLastDamageTime();
	void damage();
	int getHP();

private:
	const float BULLET_SPEED = 10.f;
	const long long BULLET_TIMEOUT = 10;

	sf::ConvexShape _ship;
	float _speedX;
	float _speedY;
	float _size;
	int _hp;
	long _timeSinceLastDamage = 0;
	sf::Vector2f _dir;
	long _timeSinceLastShoot = 0;

	void draw(sf::RenderTarget& target, const sf::RenderStates& states) const override;

};

