#pragma once
#include <iostream>
#include <fstream>

class Engine
{
private:
		int width;
		int height;
		sf::RenderWindow window;
		// Prywatny konstruktor, aby uniemo¿liwiæ tworzenie instancji z zewn¹trz, sprawdzenie czy okno zostalo poprawnie zainicjowane
		Engine(int w, int h) : width(w), height(h), window(sf::VideoMode(w, h), "Engine2D") {
			if (!window.isOpen() ) {
				// Zapisanie komunikatu o bledzie w pliku logfile.txt
				std::ofstream logfile("logfile.txt");
				if (logfile.is_open() ){
					logfile << "B³¹d inicjalizacji okna." << std::endl;
					logfile.close();
				}
				std::cerr << "B³¹d inicjalizacji okna. Zobacz plik logfile.txt dla wiêcej informacji." << std::endl;
				// Zakoñcz pracê silnika
				exit(1);
			}
		};

public:
	// Metoda zwracaj¹ca instancjê singletona
	static Engine& getInstance(int w = 800, int h = 600) {
		static Engine instance(w, h);
		return instance;
	}
	// Czyszczenie bitmap
	void clearScreen(sf::RenderTarget& target, const sf::Color& color = sf::Color::Black) {
		target.clear(color);
	}


	Engine(const Engine&) = delete; // Wy³¹czenie konstruktora kopiuj¹cego
	Engine& operator = (const Engine&) = delete; // Wy³¹czenie operatora przypisania

	void run() {
		while (window.isOpen()) {
			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear(sf::Color::Black);
			window.display();
		}
	}
};

