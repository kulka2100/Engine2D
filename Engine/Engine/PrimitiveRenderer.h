#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>


class PrimitiveRenderer {

public:
	const float M_PI = 3.14159f;

	void drawLine(int x0, int y0, int x1, int y1, sf::RenderWindow& window, sf::Color color);

	// Nie dziala
	void drawCircle(int xc, int yc, int r, sf::RenderWindow& window, sf::Color color);

};

