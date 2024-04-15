#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>


class PrimitiveRenderer {

public:
	PrimitiveRenderer();
	float c1, c2;

	void drawLine(int x0, int y0, int x1, int y1, sf::RenderWindow& window, sf::Color color);

	// Algorytm rysowania okregu - osmiokrotna symetria
	void drawCircle(int xc, int yc, int r, sf::RenderWindow& window, sf::Color color);

	//Rysowanie Elipsy
	void drawElipse(int xc, int yc, int a, int b, sf::RenderWindow& window, sf::Color color);

	void drawRectangle(std::vector<sf::Vector2f>& vertices, sf::RenderWindow& window, sf::Color color);

	void drawPlayer(int r, sf::RenderWindow& window, sf::Color color);

	void move(float x, float y);

};

