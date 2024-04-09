#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "PrimitiveRenderer.h"

class Point2D
{
private:
	sf::Vector2f point;
	float x, y;
	sf::Vector2f direction;
	float speed;
	

public:
	Point2D() {};

	Point2D(float x, float y, sf::Vector2f dir, float spd) : point(x, y), direction(dir), speed(spd) {}

	void setPoint(float x, float y);

	void update();

	sf::Vector2f getPoint() {
		return point;
	}

	void drawPoint(Point2D& ptk, sf::RenderWindow& window, sf::Color color);


};

