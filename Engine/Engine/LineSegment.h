#pragma once
#include "Point2D.h"
#include "PrimitiveRenderer.h"

class LineSegment
{
private:
	Point2D a, b;
	int x0, y0, x1, y1;

public:
	LineSegment(Point2D& a, Point2D& b) {
		this->a = a;
		this->b = b;
	}

	std::pair<Point2D, Point2D> getPoints() {
		return std::make_pair(a, b);
	}

	LineSegment(int x0, int y0, int x1, int y1) {
		this->x0 = x0;
		this->y0 = y0;
		this->x1 = x1;
		this->y1 = y1;
	}


	void setPoints(Point2D& a, Point2D& b) {
		this->a = a;
		this->b = b;
	}


	void drawL(PrimitiveRenderer& line, sf::RenderWindow& window, sf::Color color) const {
		line.drawLine(x0, y0, x1, y1, window, color);
	}


};

