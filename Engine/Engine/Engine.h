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


class Engine
{
private:
		int width;
		int height;
		int limitFramrate;
		bool fullscreen;
		int moveCounter;
		sf::Color bgColor;
		sf::RenderWindow window;
		// Prywatny konstruktor, aby uniemozliwic tworzenie instancji z zewn�trz. sprawdzenie czy okno zostalo poprawnie zainicjowane
		Engine(int w, int h, bool fullscreen);
		// Obiekt do obsługi bitmapy
		BitmapHandler bitmapHandler;
		AnimationHandler animationHandler;

		sf::Texture backgroundTexture;
		sf::Sprite backgroundSprite;

public:
	// Metoda zwracajaca instancje singletona, zmienna static Engine inicjalizowana jest tylko raz i istnieje do ko�ca pracy programu
	static Engine& getInstance(int w, int h, bool fullscreen) {
		static Engine instance(w, h, fullscreen);
		return instance;
	}

	sf::RenderWindow& getWindow() {
		return window;
	}

	//Metoda ustawiaj�ca pozwalajaca ustawic pelny ekran.sf::VideoMode::getFullscreenModes() zwraca liste obslugiwanych przez system trybow pelnoekranowych.[0] oznacza wybor pierwszego z listy
	void setFullscreen(bool fullscreen);

	// Metoda ustawia wielkosc okna
	void setWindowSize(int w, int h);

	// Czyszczenie bitmap
	void clearScreen(sf::RenderTarget& target, const sf::Color& color = sf::Color::Black);

	Engine(const Engine&) = delete; // Wyylczenie konstruktora kopiujacego
	Engine& operator = (const Engine&) = delete; // Wylaczenie operatora przypisania

	//Metoda ustawiajaca limit klatek na sekunde
	void setLimit(int limit);

	void createBitmap(int width, int height) {
		bitmapHandler.createBitmap(width, height);
	}

	void deleteBitmap() {
		bitmapHandler.deleteBitmap();
	}

	bool loadBitmapFromFile(const std::string& filename) {
		return bitmapHandler.loadFromFile(filename);
	}

	bool saveBitmapToFile(const std::string& filename) {
		return bitmapHandler.saveToFile(filename);
	}

	void copyBitmapFrom(const BitmapHandler& other) {
		bitmapHandler.copyFrom(other);
	}

	// Metoda wczytująca tło z pliku
	bool loadBackground(const std::string& filename);

	// Metoda rysująca tło
	void drawBackground();

	//Glowna petla
	void run();

	// Zamknięcie okna przed deinicjacja
	~Engine() {
		window.close();
	}

};

