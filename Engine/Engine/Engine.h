#pragma once
#include <iostream>
#include <fstream>

class Engine
{
private:
		int width;
		int height;
		sf::RenderWindow window;
		int limitFramrate;
		bool fullScreen;
		// Prywatny konstruktor, aby uniemo�liwi� tworzenie instancji z zewn�trz. sprawdzenie czy okno zostalo poprawnie zainicjowane
		// Po ":" wypisujemy liste inicjalizacyjn� zastepujaca np. this->width = w;
		Engine(int w, int h) : width(w), height(h), window(sf::VideoMode(w, h), "Engine2D") {
			if (!window.isOpen() ) {
				// Zapisanie komunikatu o bledzie w pliku logfile.txt
				std::ofstream logfile("logfile.txt");
				if (logfile.is_open() ){
					logfile << "B��d inicjalizacji okna." << std::endl;
				}
				else {
					std::cerr << "Blad otwarcia pliku do zapisu." << std::endl;
				}
				logfile.close();

				std::cerr << "B��d inicjalizacji okna. Zobacz plik logfile.txt dla wi�cej informacji." << std::endl;
				// Zako�cz prac� silnika
				exit(1);
			}
			

		};

public:
	// Metoda zwracaj�ca instancj� singletona, zmienna static Engine inicjalizowana jest tylko raz i istnieje do ko�ca pracy programu
	static Engine& getInstance(int w, int h) {
		static Engine instance(w, h);
		return instance;
	}

	// Czyszczenie bitmap
	void clearScreen(sf::RenderTarget& target, const sf::Color& color = sf::Color::Black) {
		target.clear(color);
	}

	Engine(const Engine&) = delete; // Wy��czenie konstruktora kopiuj�cego
	Engine& operator = (const Engine&) = delete; // Wy��czenie operatora przypisania

	//Metoda ustawiajaca limit klatek na sekunde
	void setLimit(int limit) {
		this->limitFramrate = limit;
	}

	//Metoda ustawiaj�ca pozwalaj�ca ustawi� pe�ny ekran.sf::VideoMode::getFullscreenModes() zwraca list� obs�ugiwanych przez system tryb�w pe�noekranowych.[0] oznacza wyb�r pierwszego z listy
	void setFullScreen(bool full) {
		this->fullScreen = full;
		if (fullScreen) {
			window.create(sf::VideoMode::getFullscreenModes()[0], "Engine2D Full Screen", sf::Style::Fullscreen);
		}
	}

	void run() {
		window.setFramerateLimit(limitFramrate);
		sf::RectangleShape rect(sf::Vector2f(50.f, 100.f)); //Na potrzeby testu

		sf::Clock clock;

		while (window.isOpen()) {
			//Pobiera czas, kt�ry up�yn�� od ostatniego wywo�ania clock.restart()
			sf::Time deltaTime = clock.restart();
			sf::Event event;

			//Nasluchiwnie zdarzen
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();

				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						std::cout << "Wcisnieto lewy przycisk myszy" << std::endl;
						//dalsza obsluga zdarzenia
					}
					else if (event.mouseButton.button == sf::Mouse::Right) {
						std::cout << "Wcisnieto prawy przycisk myszy" << std::endl;
						//dalsza obsluga zdarzenia
					}
				}

				if (event.type == sf::Event::MouseMoved) {
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					std::cout << "Pozycja myszy: " << mousePosition.x << ", " << mousePosition.y << std::endl;
				}

			}

			rect.move(0.5f, 0.1f);

			window.clear(sf::Color::Black);
			window.draw(rect);

			window.display();

			std::cout << "Czas trwania klatki: " << deltaTime.asSeconds() << " sekundy" << std::endl;
		}
	}
};

