#include "Point2D.h"


void Point2D::setPoint(float x, float y) {
	point.x = x;
	point.y = y;
}

void Point2D::drawPoint(Point2D& ptk, sf::RenderWindow& window, sf::Color color) {
	sf::VertexArray points(sf::Points);

	points.append(sf::Vector2f(point.x, point.y));
	points[0].color = color;
	window.draw(points);
}
