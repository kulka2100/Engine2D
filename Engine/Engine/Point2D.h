#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "ShapeObject.h"


class Point2D : public ShapeObject
{
protected:
	sf::Vector2f point;
	float x, y;
	

public:
	Point2D() : ShapeObject(), point(0.0f, 0.0f) {}
	Point2D(float x, float y) : ShapeObject(), point(x, y) {}

	Point2D(sf::Vector2f point) {
		this->point = point;
	}


	void setPoint(float x, float y);


	sf::Vector2f getPoint() {
		return point;
	}

	void draw(sf::RenderWindow& window, sf::Color color) override;

	void drawPoint(Point2D& ptk, sf::RenderWindow& window, sf::Color color);
};

