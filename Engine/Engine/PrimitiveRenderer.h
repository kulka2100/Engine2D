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
#include "ShapeObject.h"


class PrimitiveRenderer : public ShapeObject {

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

	void drawPlayer(int a, int b, sf::RenderWindow& window, sf::Color color);

	void move(float x, float y);

	void draw(sf::RenderWindow& window, sf::Color color) override;
	
	//Rysowanie lamanych linii - otwartych lub zamknietych
	void drawBrokenLine(std::vector<Point2D>& points, sf::RenderWindow& window, sf::Color color, bool closed);

	//Narysowanie wielokata wypelnionego kolorem, algorytm z kontrola parzystosci
	void filledPolygon(const std::vector<sf::Vector2f>& vertices, sf::RenderWindow& window, sf::Color fillColor);

	//Algorytm floodFill
	static void floodFill(const sf::Vector2i& startPoint, sf::RenderWindow& window, sf::Color fillColor, sf::Color backgroundColor);

	static void borderFill(const sf::Vector2i& startPoint, sf::RenderWindow& window, sf::Color fillColor, sf::Color boundryColor);


	void drawSimplePolygon(std::vector<Point2D> vertices, sf::RenderWindow& window, sf::Color color);

	// Funkcja do sprawdzania przeciêcia odcinków
	static bool segmentsIntersect(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2);

	// Funkcja pomocnicza do obliczania orientacji
	static float orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);




};

