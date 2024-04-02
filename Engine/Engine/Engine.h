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
		BitmapHandler bitmapa;

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

	// Metoda do wczytywania bitmapy z pliku
	void zaladujBitmape(const std::string& nazwaPliku);

	// Metoda do zapisywania bitmapy do pliku
	void zapiszBitmape(const std::string& nazwaPliku);

	// Metoda do kopiowania fragmentu bitmapy
	void skopiujBitmapyZSilnika(int x, int y, int szerokosc, int wysokosc);

	//Glowna petla
	void run();

	// Zamknięcie okna przed deinicjacja
	~Engine() {
		window.close();
	}

};

