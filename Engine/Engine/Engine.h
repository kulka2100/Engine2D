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
		Engine(int w, int h, bool fullscreen) : width(w), height(h), fullscreen(fullscreen), window(sf::VideoMode(w, h), "Engine2D") {
			if (fullscreen) {
				window.create(sf::VideoMode(w, h), "Engine2D", sf::Style::Fullscreen);
			}
			else {
				window.create(sf::VideoMode(w, h), "Engine2D");
			}
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
	static Engine& getInstance(int w, int h, bool fullscreen) {
		static Engine instance(w, h, fullscreen);
		return instance;
	}

	// Metoda pozwalaj�ca ustawi� pe�ny ekran
	void setFullscreen(bool fullscreen) {
		this->fullscreen = fullscreen;
		if (fullscreen) {
			window.create(sf::VideoMode(width, height), "Engine2D", sf::Style::Fullscreen);
		}
		else {
			window.create(sf::VideoMode(width, height), "Engine2D");
		}
	}

	// Metoda ustawia wielko�� okna
	void setWindowSize(int w, int h) {
		width = w;
		height = h;
		window.setSize(sf::Vector2u(width, height));
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

				// Ustawienie ekranu na rozdzielczosc 800x600 skr�tem ALT+R
				if (event.type == sf::Event::KeyPressed) {
					if ((event.key.code == sf::Keyboard::R) && (event.key.alt)) {
						if (fullscreen) {
							setFullscreen(false);
							setWindowSize(800, 600);
						}
						else {
							setWindowSize(800, 600);
						}
					}
				}

				// Ustawienie pe�nego ekranu skr�tem ALT+F (F-fullscreen)
				if (event.type == sf::Event::KeyPressed) {
					if ((event.key.code == sf::Keyboard::F) && (event.key.alt)) {
						setFullscreen(true);
					}
				}

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

			// W��czenie synchronizacji pionowej
			window.setVerticalSyncEnabled(true);

			window.clear(sf::Color::Black);
			window.draw(rect);

			window.display();

			std::cout << "Czas trwania klatki: " << deltaTime.asSeconds() << " sekundy" << std::endl;
		}
	}
};

