#include "PrimitiveRenderer.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include "Engine.h"
#include <stack>


PrimitiveRenderer::PrimitiveRenderer() : ShapeObject(), c1(400), c2(700) {}

void PrimitiveRenderer::draw(sf::RenderWindow& window, sf::Color color) {
	// Rysowanie linii
	drawLine(100, 100, 200, 200, window, color);

	// Rysowanie okregu
	drawCircle(300, 300, 50, window, color);

	// Rysowanie elipsy
	drawElipse(400, 400, 60, 30, window, color);

	// Rysowanie prostokata
	std::vector<sf::Vector2f> rectangleVertices = { {500, 500}, {600, 500}, {600, 600}, {500, 600} };
	drawPolygon(rectangleVertices, window, color);

}


void PrimitiveRenderer::putPixel(float x, float y, sf::RenderWindow& window, sf::Color color) {
	sf::VertexArray points(sf::Points);

	points.append(sf::Vector2f(x, y));
	points[0].color = color;
	window.draw(points);
}



sf::Color PrimitiveRenderer::getPixel(sf::Vector2i pixelPos, sf::RenderWindow& window) {
	sf::Texture texture;
	texture.create(window.getSize().x, window.getSize().y);
	texture.update(window);

	// Utwórz obraz na podstawie tekstury
	sf::Image image = texture.copyToImage();

	sf::Color pixelColor = image.getPixel(pixelPos.x, pixelPos.y);

	// Wyœwietl pobrany kolor w konsoli
	std::cout << "Pobrany kolor piksela (" << pixelPos.x << ", " << pixelPos.y << "): R="
		<< static_cast<int>(pixelColor.r) << ", G=" << static_cast<int>(pixelColor.g)
		<< ", B=" << static_cast<int>(pixelColor.b) << std::endl;

	// Pobierz kolor piksela na podanych wspó³rzêdnych
	return pixelColor;
}





void PrimitiveRenderer:: drawLine(int x0, int y0, int x1, int y1, sf::RenderWindow& window, sf::Color color) {
	// Tablica wierzcholkow reprezentujacych linie
	sf::VertexArray line(sf::Points, 2);
	int x;
	float dy, dx, y, m;

	dy = y1 - y0;
	dx = x1 - x0;
	y = y0;
	m = dy / dx;

	// Sprawdzenie czy odcinek jest stromy
	bool steep = abs(dy) > abs(dx);

	line[0].color = color;
	line[1].color = color;

	if (!steep) {
		line[0].position = sf::Vector2f(x0, y0);
		for (x = x0; x <= x1; x++) {
			line[1].position = sf::Vector2f(x + 1, y);
			window.draw(line);
			y += m;
		}
	}
	else {
		line[0].position = sf::Vector2f(y0, x0);
		for (x = y0; x <= y1; x++) {
			line[1].position = sf::Vector2f(x, y + 1);
			window.draw(line);
			y += m;
		}
	}
}



// Algorytm rysowania okregu - osmiokrotna symetria
void PrimitiveRenderer::drawCircle(int xc, int yc, int r, sf::RenderWindow& window, sf::Color color) {
	int x = 0;
	int y = r;
	int p = 3 - (2 * r);
	int vertexIndex = 0;
	sf::VertexArray circ(sf::Points, r * 8);

	//Dopoki nie narysujemy 1/8 czesci okregu
	while (x <= y) {
		//Rysowanie 8 pikseli na ekranie korzystajac z symetrii okregu
		circ[vertexIndex++].position = sf::Vector2f(xc + x, yc + y);
		circ[vertexIndex++].position = sf::Vector2f(xc - x, yc + y);
		circ[vertexIndex++].position = sf::Vector2f(xc + x, yc - y);
		circ[vertexIndex++].position = sf::Vector2f(xc - x, yc - y);
		circ[vertexIndex++].position = sf::Vector2f(xc + y, yc + x);
		circ[vertexIndex++].position = sf::Vector2f(xc - y, yc + x);
		circ[vertexIndex++].position = sf::Vector2f(xc + y, yc - x);
		circ[vertexIndex++].position = sf::Vector2f(xc - y, yc - x);

		x++;
		//jesli p <= 0, punkt znajduje sie wewnatrz okregu, zwiekszamy wtedy x, y pozostaje bez zmian
		if (p <= 0) {
			p += 4 * x + 6;
		}
		// W przeciwnym wypadku punkt lezy na zewnatrz, zmniejszamy wtedy y i zwiekszamy x
		else {
			p += 4 * (x - y) + 10;
			y--;
		}
	}

	for (int i = 0; i < circ.getVertexCount(); ++i) {
		circ[i].color = color;
	}	
	window.draw(circ);

}


// Algorytm rysowania okregu - osmiokrotna symetria
void PrimitiveRenderer::drawPlayer(int a, int b, sf::RenderWindow& window, sf::Color color) {
	sf::VertexArray elipse(sf::Points);
	int xc = this->GameObject::getX();
	int yc = this->GameObject::getY();

	// zmienne a i b reprezentuja poszczegolne promienie elipsy
	for (int x = -a; x <= a; x++) {
		int y = (b * sqrt(1 - (1.0 * x * x) / (a * a)));
		elipse.append(sf::Vector2f(xc + x, yc + y));
		elipse.append(sf::Vector2f(xc + x, yc - y));
	}

	//uzylem dwoch petli w przypadku jednej powstawaly dziury
	for (int y = -b; y <= b; y++) {
		int x = (a * sqrt(1 - (1.0 * y * y) / (b * b)));

		elipse.append(sf::Vertex(sf::Vector2f(xc + x, yc + y)));
		elipse.append(sf::Vertex(sf::Vector2f(xc - x, yc + y)));
	}


	for (int i = 0; i < elipse.getVertexCount(); i++)
		elipse[i].color = color;

	window.draw(elipse);

}

void PrimitiveRenderer::drawElipse(int xc, int yc, int a, int b, sf::RenderWindow& window, sf::Color color) {
	sf::VertexArray elipse(sf::Points);

	// zmienne a i b reprezentuja poszczegolne promienie elipsy
	for (int x = -a; x <= a; x++) {
		int y =(b * sqrt(1 - (1.0 * x * x) / (a * a)));
			elipse.append(sf::Vector2f(xc + x, yc + y));
			elipse.append(sf::Vector2f(xc + x, yc - y));
	}

	//uzylem dwoch petli w przypadku jednej powstawaly dziury
	for (int y = -b; y <= b; y++) {
		int x = (a * sqrt(1 - (1.0 * y * y) / (b * b)));

		elipse.append(sf::Vertex(sf::Vector2f(xc + x, yc + y)));
		elipse.append(sf::Vertex(sf::Vector2f(xc - x, yc + y)));
	}

	
	for (int i = 0; i < elipse.getVertexCount(); i++) 
		elipse[i].color = color;

	window.draw(elipse);
}




//Rysowanie prostokatow
void PrimitiveRenderer::drawPolygon(std::vector<sf::Vector2f>& vertices, sf::RenderWindow& window, sf::Color color) {
	sf::VertexArray outline(sf::LinesStrip);


	for (size_t i = 0; i < vertices.size(); i++) {
		outline.append(vertices[i]);
	}

	outline.append(vertices[0]);

	for (int i = 0; i < outline.getVertexCount(); ++i) {
		outline[i].color = color;
	}

	window.draw(outline);

}

void PrimitiveRenderer::move(float x, float y) {
	float currentX, currentY;
	this->GameObject::getPosition(currentX, currentY);
	this->GameObject::setPosition(currentX + x, currentY + y);
}



void PrimitiveRenderer::drawBrokenLine(std::vector<Point2D>& points, sf::RenderWindow& window, sf::Color color, bool closed) {
	sf::VertexArray lines(sf::LinesStrip);

	for (size_t i = 0; i < points.size(); i++) {
		lines.append(sf::Vertex(points[i].getPoint(), color));
	}

	if (closed && points.size() > 0) {
		lines.append(lines[0]);
	}
	window.draw(lines);
}

void PrimitiveRenderer::filledPolygon(const std::vector<sf::Vector2f>& vertices, sf::RenderWindow& window, sf::Color fillColor) {
	// Znajd  najni szy i najwy szy punkt wielok ta
	float minY = vertices[0].y, maxY = vertices[0].y;
	for (size_t i = 1; i < vertices.size(); ++i) {
		if (vertices[i].y < minY) minY = vertices[i].y;
		if (vertices[i].y > maxY) maxY = vertices[i].y;
	}

	// Przejd  przez ka d  lini  skanuj c 
	for (int y = static_cast<int>(minY); y <= static_cast<int>(maxY); ++y) {
		std::vector<float> intersections;

		// Znajd  punkty przeci cia z kraw dziami wielok ta
		for (size_t i = 0; i < vertices.size(); ++i) {
			size_t next = (i + 1) % vertices.size();
			float y1 = vertices[i].y, y2 = vertices[next].y;
			if ((y1 <= y && y < y2) || (y2 <= y && y < y1)) {
				float x = vertices[i].x + (y - y1) * (vertices[next].x - vertices[i].x) / (y2 - y1);
				intersections.push_back(x);
			}
		}

		// Sortuj punkty przeci cia
		std::sort(intersections.begin(), intersections.end());

		// Rysuj linie mi dzy parami punkt w przeci cia
		for (size_t i = 0; i < intersections.size(); i += 2) {
			int x1 = static_cast<int>(intersections[i]);
			int x2 = static_cast<int>(intersections[i + 1]);
			for (int x = x1; x <= x2; ++x) {
				putPixel(x, y, window, fillColor);
			}
		}
	}
}

//Nie do konca dziala
 void PrimitiveRenderer::floodFill(const sf::Vector2f& startPoint, sf::RenderWindow& window, sf::Color fillColor, sf::Color backgroundColor) {
	//Utworz stos
	std::stack<sf::Vector2i> pixelStack;


	std::vector<std::vector<bool>> visitedPixels(window.getSize().x, std::vector<bool>(window.getSize().y, false));

	sf::Vector2u windowSize = window.getSize();

	if (startPoint.x < 0 || startPoint.x >= windowSize.x || startPoint.y < 0 || startPoint.y >= windowSize.y) {
		return;
	}

	//Wyswietl pixel a nastepnie zapisz go na stosie
	putPixel(startPoint.x, startPoint.y, window, fillColor);
	pixelStack.push(sf::Vector2i(static_cast<int>(startPoint.x), static_cast<int>(startPoint.y)));


	while (!pixelStack.empty()) {
		//Zapisz ostatni element ze stosu w zmiennej pixel, a nastepnie zdejmij ten element ze stosu
		sf::Vector2i pixel = pixelStack.top();
		pixelStack.pop();

		if (!visitedPixels[pixel.x][pixel.y]) {

			visitedPixels[pixel.x][pixel.y] = true;


			// pobranie koloru akutalnego pixela
		sf::Color currentColor = getPixel(pixel, window);

		//Jesli pixel ze stosu jest taki sam jak ten ekranie zamien kolor
		if (currentColor == backgroundColor) {
			putPixel(pixel.x, pixel.y, window, fillColor);
			//Umiesc 4 sasiadow tego pixela na stosie
			pixelStack.push(sf::Vector2i(pixel.x + 1, pixel.y));
			pixelStack.push(sf::Vector2i(pixel.x - 1, pixel.y));
			pixelStack.push(sf::Vector2i(pixel.x, pixel.y + 1));
			pixelStack.push(sf::Vector2i(pixel.x, pixel.y - 1));

			}
		}
	}

}
