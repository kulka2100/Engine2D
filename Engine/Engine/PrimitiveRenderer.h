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

/**
 * @class primitiverenderer
 * @brief klasa reprezentuj¹ca obiekt renderuj¹cy podstawowe kszta³ty
 */
class PrimitiveRenderer : public ShapeObject {

public:
	/**
	* @brief kontruktor klas y PrimitiveRenderer
	*/
	PrimitiveRenderer();
	float c1, c2;/**< pola klasy odpowiadajace za wspolrzedne */

	/**
     * @brief metoda statyczna rysujaca pojedynczy piksel na oknie
     * @param x wspolrzedna X piksela
     * @param y wspolrzedna Y piksela
     * @param window okno renderowania
     * @param color kolor piksela
     */
	static void putPixel(float x, float y, sf::RenderWindow& window, sf::Color color);

	/**
	 * @brief pobieranie koloru pixela
	 * @param pixelpos pozycja piksela
	 * @param window okno renderowania
	 * @return kolor piksela na danej pozycji
	 */
	static sf::Color getPixel(sf::Vector2i pixelPos, sf::RenderWindow& window);

	/**
	 * @brief metoda rysujaca linie miedzy dwoma punktami
	 * @param x0 wspolrzedna X pierwszego punktu
	 * @param y0 wspolrzedna Y pierwszego punktu
	 * @param x1 wspolrzedna X drugiego punktu
	 * @param y1 wspolrzedna Y drugiego punktu
	 * @param window okno renderowania
	 * @param color kolor linii
	 */
	void drawLine(int x0, int y0, int x1, int y1, sf::RenderWindow& window, sf::Color color);

	/**
	 * @brief Algorytm rysowania okregu - osmiokrotna symetria
	 * @param xc wspolrzedna X srodka okregu
	 * @param yc wspolrzedna Y srodka okregu
	 * @param r promien okregu
	 * @param window okno renderowania
	 * @param color kolor okregu
	 */
	void drawCircle(int xc, int yc, int r, sf::RenderWindow& window, sf::Color color);

	/**
	 * @brief Rysowanie Elipsy
	 * @param xc wspolrzedna X srodka elipsy
	 * @param yc wspolrzedna Y srodka elipsy
	 * @param a srednica a elipsy
	 * @param b srednica b elipsy
	 * @param window okno renderowania
	 * @param color kolor elipsy
	 */
	void drawElipse(int xc, int yc, int a, int b, sf::RenderWindow& window, sf::Color color);

	/**
	 * @brief Rysowanie wielokata
	 * @param vertices wektor wspolrzednych
	 * @param window okno renderowania
	 * @param color kolor elipsy
	 */
	void drawPolygon(std::vector<sf::Vector2f>& vertices, sf::RenderWindow& window, sf::Color color);

	/**
	 * @brief poczatkowo metoda odpowiadajaca za rysowanie gracza w ksztalcie elipsy
	 * @param xc wspolrzedna X srodka gracza
	 * @param yc wspolrzedna Y srodka gracza
	 * @param a srednica a elipsy
	 * @param b srednica b elipsy
	 * @param window okno renderowania
	 * @param color kolor elipsy
	 */
	void drawPlayer(int a, int b, sf::RenderWindow& window, sf::Color color);

	/**
	 * @brief metoda odpowiadajaca za przesuwanie obiektu
	 * @param x wartosc przesuniecia w poziomie
	 * @param y wartosc przesuniecia w pionie
	 */
	void move(float x, float y);

	/**
	 * @brief metoda rysujaca przykladowe obiekty w oknie
	 * @param window okno renderowania
	 * @param color kolor obiektu
	 */
	void draw(sf::RenderWindow& window, sf::Color color) override;
	
	/**
	 * @brief Rysowanie lamanych linii - otwartych lub zamknietych
	 * @param points punkty odpowiadajace za wspolrzedne linii
	 * @param window okno renderowania
	 * @param color kolor obiektu
	 * @param closed parametr logiczny odpowiadajacy za to czy figura jest domknieta
	 */
	void drawBrokenLine(std::vector<Point2D>& points, sf::RenderWindow& window, sf::Color color, bool closed);

	/**
	 * @brief Narysowanie wielokata wypelnionego kolorem, algorytm z kontrola parzystosci
	 * @param vertices wektor wspolrzednych
	 * @param window okno renderowania
	 * @param color kolor elipsy
	 */
	void filledPolygon(const std::vector<sf::Vector2f>& vertices, sf::RenderWindow& window, sf::Color fillColor);

	/**
	 * @brief Algorytm floodFill
	 * @param vertices wektor wspolrzednych
	 * @param window okno renderowania
	 * @param fillColor kolor wypelnienia
	 * @param backgroundColor kolor tla
	 */
	static void floodFill(const sf::Vector2i& startPoint, sf::RenderWindow& window, sf::Color fillColor, sf::Color backgroundColor);

	/**
	 * @brief Algorytm borderFill
	 * @param vertices wektor wspolrzednych
	 * @param window okno renderowania
	 * @param fillColor kolor wypelnienia
	 * @param boundryColor kolor granicy figury 
	 */
	static void borderFill(const sf::Vector2i& startPoint, sf::RenderWindow& window, sf::Color fillColor, sf::Color boundryColor);

	/**
	 * @brief rysuje wielokat
	 * @param vertices wektor wspolrzednych
	 * @param window okno renderowania
	 * @param color kolor wielokata
	 */
	void drawSimplePolygon(std::vector<Point2D> vertices, sf::RenderWindow& window, sf::Color color);

	/**
	 * @brief Funkcja do sprawdzania przeciêcia odcinków
	 * @param p1 punkt do weryfikacji 
	 * @param p2 punkt do weryfikacji
	 * @param q1 punkt do weryfikacji
	 * @param q2 punkt do weryfikacji
	 */
	static bool segmentsIntersect(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f q1, sf::Vector2f q2);

	/**
	 * @brief Funkcja pomocnicza do obliczania orientacji
	 * @param p punkt do weryfikacji
	 * @param q punkt do weryfikacji
	 * @param r punkt do weryfikacji
	 */
	static float orientation(sf::Vector2f p, sf::Vector2f q, sf::Vector2f r);
};

