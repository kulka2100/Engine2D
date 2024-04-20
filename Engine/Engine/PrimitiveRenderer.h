#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Point2d.h"


class PrimitiveRenderer {

public:
	PrimitiveRenderer();
	float c1, c2;

	static void putPixel(float x, float y, sf::RenderWindow& window, sf::Color color);

	//Pobieranie koloru pixela
	static sf::Color getPixel(sf::Vector2i pixelPos, sf::RenderWindow& window);

	void drawLine(int x0, int y0, int x1, int y1, sf::RenderWindow& window, sf::Color color);

	// Algorytm rysowania okregu - osmiokrotna symetria
	void drawCircle(int xc, int yc, int r, sf::RenderWindow& window, sf::Color color);

	//Rysowanie Elipsy
	void drawElipse(int xc, int yc, int a, int b, sf::RenderWindow& window, sf::Color color);

	void drawPolygon(std::vector<sf::Vector2f>& vertices, sf::RenderWindow& window, sf::Color color);

	void drawPlayer(int r, sf::RenderWindow& window, sf::Color color);

	void move(float x, float y);
	
	//Rysowanie lamanych linii
	void drawBrokenLine(std::vector<Point2D>& points, sf::RenderWindow& window, sf::Color color, bool closed);

	//Narysowanie wielokata wypelnionego kolorem, algorytm z kontrola parzystosci
	void filledPolygon(const std::vector<sf::Vector2f>& vertices, sf::RenderWindow& window, sf::Color fillColor);

	//Algorytm floodFill. mam problem jak go zastosowac w kodzie
	static void floodFill(const sf::Vector2f& startPoint, sf::RenderWindow& window, sf::Color fillColor, sf::Color backgroundColor);

};

