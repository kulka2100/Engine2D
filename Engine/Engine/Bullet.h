#pragma once
#include "Point2D.h"
class Bullet : public Point2D
{
private:
	sf::Vector2f direction;
	float speed;

public:
	Bullet(float x, float y, sf::Vector2f dir, float spd) : Point2D(x, y), direction(dir), speed(spd) {};
	void update();
};
