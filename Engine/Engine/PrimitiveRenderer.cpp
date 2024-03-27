#include "PrimitiveRenderer.h"

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
	int x = r;
	int y = 0;
	int p = 1 - r;
	int vertexIndex = 0;
	sf::VertexArray circ(sf::Points, r * 8);

	while (x >= y) {
		//Rysowanie 8 pikseli na ekranie korzystajac z symetrii okregu
		circ[vertexIndex++].position = sf::Vector2f(xc + x, yc + y);
		circ[vertexIndex++].position = sf::Vector2f(xc - x, yc + y);
		circ[vertexIndex++].position = sf::Vector2f(xc + x, yc - y);
		circ[vertexIndex++].position = sf::Vector2f(xc - x, yc - y);
		circ[vertexIndex++].position = sf::Vector2f(xc + y, yc + x);
		circ[vertexIndex++].position = sf::Vector2f(xc - y, yc + x);
		circ[vertexIndex++].position = sf::Vector2f(xc + y, yc - x);
		circ[vertexIndex++].position = sf::Vector2f(xc - y, yc - x);

		y++;

		if (p < 0) {
			p += 2 * y + 1;
		}
		else {
			x--;
			p += 2 * (y - x + 1);
		}
	}

	for (int i = 0; i < circ.getVertexCount(); ++i) {
		circ[i].color = color;
	}
	window.draw(circ);
}


//Rysowanie prostokatow
void PrimitiveRenderer::drawRectangle(std::vector<sf::Vector2f>& vertices, sf::RenderWindow& window, sf::Color color) {
	sf::VertexArray rectangle(sf::Points, 4);
	//nowa tablica do ustawienia koloru rysowanych linii
	sf::VertexArray outline(sf::LinesStrip, 5);

	if (vertices.size() == 4)
		for (size_t i = 0; i < 4; i++)
			rectangle[i].position = vertices[i];
	//
	outline[0].position = rectangle[0].position;
	outline[1].position = rectangle[1].position;
	outline[2].position = rectangle[2].position;
	outline[3].position = rectangle[3].position;
	outline[4].position = rectangle[0].position;

	for (int i = 0; i < 5; ++i) {
		outline[i].color = color;
	}

	window.draw(outline);
}