#pragma once
#include <iostream>
#include <fstream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include "PrimitiveRenderer.h"
#include "BitmapHandler.h"
#include "Point2D.h"
#include "Bullet.h"
#include "AnimationHandler.h"

/**
 * @class Engine
 * @brief Klasa reprezentujaca glowny silnik gry
 */
class Engine
{
private:
	int width; /**< Szerokosc okna */
	int height; /**< Wysokosc okna */
	int limitFramrate; /**< Limit klatek na sekunde */
	bool fullscreen; /**< Flaga okreslająca tryb pelnoekranowy */
	int moveCounter; /**< Licznik ruchu */
	sf::Color bgColor; /**< Kolor tla */
	sf::RenderWindow window; /**< Okno renderowania */
	BitmapHandler bitmapHandler; /**< Obiekt do obslugi bitmapy */
	AnimationHandler animationHandler; /**< Obiekt do obslugi animacji */
	sf::Texture backgroundTexture; /**< Tekstura tla */
	sf::Sprite backgroundSprite; /**< Sprite tla */

	/**
	 * @brief Prywatny konstruktor, aby uniemozliwic tworzenie instancji z zewnatrz. sprawdzenie czy okno zostalo poprawnie zainicjowane
	 * @param w Szerokosc okna
	 * @param h Wysokosc okna
	 * @param fullscreen Tryb pelnoekranowy
	 */
	Engine(int w, int h, bool fullscreen);

public:
	// 
	/**
	 * @brief Metoda zwracajaca instancje singletona, zmienna static Engine inicjalizowana jest tylko raz i istnieje do konca pracy programu
	 * @param w Szerokosc okna
	 * @param h Wysokosc okna
	 * @param fullscreen Tryb pelnoekranowy
	 * @return Referencja do instancji klasy Engine
	 */
	static Engine& getInstance(int w, int h, bool fullscreen) {
		static Engine instance(w, h, fullscreen);
		return instance;
	}

	/**
	 * @brief Metoda zwracająca referencje do okna renderowania
	 * @return Referencja do okna renderowania
	 */
	sf::RenderWindow& getWindow() {
		return window;
	}

	/**
	 * @brief Metoda ustawiaj�ca pozwalajaca ustawic pelny ekran.sf::VideoMode::getFullscreenModes() zwraca liste obslugiwanych przez system trybow pelnoekranowych.[0] oznacza wybor pierwszego z listy
	 * @param fullscreen Tryb pełnoekranowy
	 */
	void setFullscreen(bool fullscreen);

	/**
	 * @brief Metoda ustawia wielkosc okna
	 * @param w Szerokość okna
	 * @param h Wysokość okna
	 */
	void setWindowSize(int w, int h);

	/**
	 * @brief Czyszczenie bitmap
	 * @param target Obiekt na którym będzie czyszczony ekran
	 * @param color Kolor którym ekran zostanie wyczyszczony
	 */
	void clearScreen(sf::RenderTarget& target, const sf::Color& color = sf::Color::Black);

	/**
	 * @brief  Wyylczenie konstruktora kopiujacego
	 */
	Engine(const Engine&) = delete; 

	/**
	 * @brief Wylaczenie operatora przypisania
	 */
	Engine& operator = (const Engine&) = delete;

	/**
     * @brief Metoda ustawiajaca limit klatek na sekunde
     * @param limit Limit klatek na sekunde
     */
	void setLimit(int limit);

	/**
	 * @brief Metoda tworzaca bitmape
	 * @param width Szerokosc bitmapy
	 * @param height Wysokosc bitmapy
	 */
	void createBitmap(int width, int height) {
		bitmapHandler.createBitmap(width, height);
	}

	/**
	 * @brief Metoda usuwajaca bitmape
	 */
	void deleteBitmap() {
		bitmapHandler.deleteBitmap();
	}

	/**
	 * @brief Metoda wczytujaca bitmape z pliku
	 * @param filename Nazwa pliku z bitmapa
	 * @return Pozytywne wczytanie bitmapy
	 */
	bool loadBitmapFromFile(const std::string& filename) {
		return bitmapHandler.loadFromFile(filename);
	}

	/**
	 * @brief Metoda zapisująca bitmapw do pliku
	 * @param filename Nazwa pliku, do którego zostanie zapisana bitmapa
	 * @return Informacja o pozytywnym wczytaniu bitmapy
	 */
	bool saveBitmapToFile(const std::string& filename) {
		return bitmapHandler.saveToFile(filename);
	}

	/**
	 * @brief Metoda kopiujaca bitmape z innej instancji BitmapHandler
	 * @param other Inna instancja BitmapHandler
	 */
	void copyBitmapFrom(const BitmapHandler& other) {
		bitmapHandler.copyFrom(other);
	}

	/**
	 * @brief Metoda wczytujaca tlo z pliku
	 * @param filename Nazwa pliku z tlem
	 * @return Wartosc logiczna informujaca o sukcesie operacji
	 */
	bool loadBackground(const std::string& filename);

	/**
	 * @brief Metoda rysujaca tlo
	 */
	void drawBackground();

	/**
	 * @brief Glowna petla gry - uruchomienie
	 */
	void run();

	/**
	 * @brief Zamknięcie okna przed deinicjacja
	 */
	~Engine() {
		window.close();
	}
};

