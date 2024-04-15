#include "PrimitiveRenderer.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include "Engine.h"


PrimitiveRenderer::PrimitiveRenderer() : c1(400), c2(700) {
	
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
void PrimitiveRenderer::drawPlayer(int r, sf::RenderWindow& window, sf::Color color) {
	int x = 0;
	int y = r;
	int p = 3 - (2 * r);
	int xc = c1;
	int yc = c2;
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

void PrimitiveRenderer::move(float x, float y) {
	c1 += x;
	c2 += y;
}

