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
		bool fullscreen;
		// Prywatny konstruktor, aby uniemo¿liwiæ tworzenie instancji z zewn¹trz. sprawdzenie czy okno zostalo poprawnie zainicjowane
		// Po ":" wypisujemy liste inicjalizacyjn¹ zastepujaca np. this->width = w;
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
					logfile << "B³¹d inicjalizacji okna." << std::endl;
				}
				else {
					std::cerr << "Blad otwarcia pliku do zapisu." << std::endl;
				}
				logfile.close();

				std::cerr << "B³¹d inicjalizacji okna. Zobacz plik logfile.txt dla wiêcej informacji." << std::endl;
				// Zakoñcz pracê silnika
				exit(1);
			}

		};

public:
	// Metoda zwracaj¹ca instancjê singletona, zmienna static Engine inicjalizowana jest tylko raz i istnieje do koñca pracy programu
	static Engine& getInstance(int w, int h, bool fullscreen) {
		static Engine instance(w, h, fullscreen);
		return instance;
	}

	// Metoda pozwalaj¹ca ustawiæ pe³ny ekran
	void setFullscreen(bool fullscreen) {
		this->fullscreen = fullscreen;
		if (fullscreen) {
			window.create(sf::VideoMode(width, height), "Engine2D", sf::Style::Fullscreen);
		}
		else {
			window.create(sf::VideoMode(width, height), "Engine2D");
		}
	}

	// Metoda ustawia wielkoœæ okna
	void setWindowSize(int w, int h) {
		width = w;
		height = h;
		window.setSize(sf::Vector2u(width, height));
	}

	// Czyszczenie bitmap
	void clearScreen(sf::RenderTarget& target, const sf::Color& color = sf::Color::Black) {
		target.clear(color);
	}

	Engine(const Engine&) = delete; // Wy³¹czenie konstruktora kopiuj¹cego
	Engine& operator = (const Engine&) = delete; // Wy³¹czenie operatora przypisania

	//Metoda ustawiajaca limit klatek na sekunde
	void setLimit(int limit) {
		this->limitFramrate = limit;
	}

	void run() {
		window.setFramerateLimit(limitFramrate);
		sf::RectangleShape rect(sf::Vector2f(50.f, 100.f)); //Na potrzeby testu

		sf::Clock clock;

		while (window.isOpen()) {
			//Pobiera czas, który up³yn¹³ od ostatniego wywo³ania clock.restart()
			sf::Time deltaTime = clock.restart();
			sf::Event event;

			//Nasluchiwnie zdarzen
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed)
					window.close();

				// Ustawienie ekranu na rozdzielczosc 800x600 skrótem ALT+R
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

				// Ustawienie pe³nego ekranu skrótem ALT+F (F-fullscreen)
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

			// W³¹czenie synchronizacji pionowej
			window.setVerticalSyncEnabled(true);

			window.clear(sf::Color::Black);
			window.draw(rect);

			window.display();

			std::cout << "Czas trwania klatki: " << deltaTime.asSeconds() << " sekundy" << std::endl;
		}
	}
};

