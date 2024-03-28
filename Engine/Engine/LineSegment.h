#pragma once
#include "Point2D.h"

class LineSegment
{
private:
	Point2D a, b;

public:
	LineSegment(Point2D& a, Point2D& b) {
		this->a = a;
		this->b = b;
	}

	std::pair<Point2D, Point2D> getPoints() {
		return std::make_pair(a, b);
	}

};

