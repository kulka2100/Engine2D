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


/**
 * @class Point2D
 * @brief klasa reprezentujaca punkt w dwuwymiarowej przestrzeni
 */
class Point2D : public ShapeObject
{
protected:
	sf::Vector2f point; /**< wspolrzedne punktu */
	float x, y; /**< wspolrzedne X i Y punktu */
	

public:
	/**
	 * @brief konstruktor domyslny klasy Point2D
	 */
	Point2D() : ShapeObject(), point(0.0f, 0.0f) {}

	/**
	 * @brief konstruktor klasy Point2D z podanymi wspolrzednymi
	 * @param x wspolrzedna X punktu
	 * @param y wspolrzedna Y punktu
	 */
	Point2D(float x, float y) : ShapeObject(), point(x, y) {}

	/**
	 * @brief konstruktor klasy Point2D z podanym wektorem
	 * @param point wektor reprezentujacy punkt
	 */
	Point2D(sf::Vector2f point) {
		this->point = point;
	}

	/**
	 * @brief metoda ustawiajaca wspolrzedne punktu
	 * @param x wspolrzedna X punktu
	 * @param y wspolrzedna Y punktu
	 */
	void setPoint(float x, float y);

	/**
	 * @brief metoda zwracajaca wspolrzedne punktu
	 * @return wspolrzedne punktu
	 */
	sf::Vector2f getPoint() const{
		return point;
	}

	/**
	 * @brief metoda rysujaca punkt na oknie
	 * @param window referencja do obiektu okna renderowania
	 * @param color kolor punktu
	 */
	void draw(sf::RenderWindow& window, sf::Color color) override;
};

