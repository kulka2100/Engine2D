#pragma once
#include "Point2D.h"
#include "PrimitiveRenderer.h"
#include "ShapeObject.h"


/**
 * @class LineSegment
 * @brief klasa reprezentujaca odcinek
 */
class LineSegment : public ShapeObject
{
private:
	Point2D a, b; /**< obiekty typu Point2D reprezentujace odcinek */
	int x0, y0, x1, y1; /**< wspolrzedne punktow definiujacych odcinek */

public:
	/**
	 * @brief konstruktor klasy LineSegment z podanymi punktami
	 * @param a pierwszy punkt odcinka
	 * @param b drugi punkt odcinka
	 */
	LineSegment(Point2D& a, Point2D& b) : ShapeObject(){
		this->a = a;
		this->b = b;
	}

	/**
	 * @brief metoda zwracajaca pare punktow definiujacych odcinek
	 * @return para punktow definiujacych odcinek
	 */
	std::pair<Point2D, Point2D> getPoints() {
		return std::make_pair(a, b);
	}

	/**
	 * @brief konstruktor klasy LineSegment z podanymi wspolrzednymi
	 * @param x0 wspolrzedna X pierwszego punktu odcinka
	 * @param y0 wspolrzedna Y pierwszego punktu odcinka
	 * @param x1 wspolrzedna X drugiego punktu odcinka
	 * @param y1 wspolrzedna Y drugiego punktu odcinka
	 */
	LineSegment(int x0, int y0, int x1, int y1) : ShapeObject() {
		this->x0 = x0;
		this->y0 = y0;
		this->x1 = x1;
		this->y1 = y1;
	}

	/**
	 * @brief metoda ustawiajaca punkty definiujace odcinek
	 * @param a pierwszy punkt odcinka
	 * @param b drugi punkt odcinka
	 */
	void setPoints(Point2D& a, Point2D& b) {
		this->a = a;
		this->b = b;
	}

	/**
	 * @brief metoda rysujaca odcinek
	 * @param line obiekt do rysowania odcinkow
	 * @param window okno renderowania, na ktorym ma zostac narysowany odcinek
	 * @param color kolor odcinka
	 */
	void drawL(PrimitiveRenderer& line, sf::RenderWindow& window, sf::Color color) const {
		line.drawLine(x0, y0, x1, y1, window, color);
	}
};

