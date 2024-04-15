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
protected:
	sf::Vector2f point;
	float x, y;
	

public:
	Point2D() {};

	Point2D(float x, float y) : point(x, y) {};

	void setPoint(float x, float y);


	sf::Vector2f getPoint() {
		return point;
	}

	void drawPoint(Point2D& ptk, sf::RenderWindow& window, sf::Color color);


};

