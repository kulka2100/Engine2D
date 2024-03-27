#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "PrimitiveRenderer.h"



// Po ":" wypisujemy liste inicjalizacyjna zastepujaca np. this->width = w;
Engine:: Engine(int w, int h, bool fullscreen) : width(w), height(h), fullscreen(fullscreen), window(sf::VideoMode(w, h), "Engine2D"), moveCounter(0) {
	if (fullscreen) {
		window.create(sf::VideoMode(w, h), "Engine2D", sf::Style::Fullscreen);
	}
	else {
		window.create(sf::VideoMode(w, h), "Engine2D");
	}
	if (!window.isOpen()) {
		// Zapisanie komunikatu o bledzie w pliku logfile.txt
		std::ofstream logfile("logfile.txt");
		if (logfile.is_open()) {
			logfile << "B??d inicjalizacji okna." << std::endl;
		}
		else {
			std::cerr << "Blad otwarcia pliku do zapisu." << std::endl;
		}
		logfile.close();

		std::cerr << "B??d inicjalizacji okna. Zobacz plik logfile.txt dla wi?cej informacji." << std::endl;
		// Zakoncz prace silnika
		exit(1);
	}
};



void Engine:: setLimit(int limit) {
	this->limitFramrate = limit;
}

void Engine:: clearScreen(sf::RenderTarget& target, const sf::Color& color) {
	target.clear(color);
}

void Engine::setFullscreen(bool fullscreen) {
	this->fullscreen = fullscreen;
	if (fullscreen) {
		window.create(sf::VideoMode::getFullscreenModes()[0], "Engine2D Full Screen", sf::Style::Fullscreen);
	}
	else {
		window.create(sf::VideoMode(width, height), "Engine2D");
	}
}

void Engine::setWindowSize(int w, int h) {
	width = w;
	height = h;
	window.setSize(sf::Vector2u(width, height));
}

void Engine::run() {
	window.setFramerateLimit(limitFramrate);
	PrimitiveRenderer newLine;
	PrimitiveRenderer circle;
	PrimitiveRenderer rectangle;


	std::vector<sf::Vector2f> vertices = {
		sf::Vector2f(100, 50),
		sf::Vector2f(200, 100),
		sf::Vector2f(200, 200),
		sf::Vector2f(100, 150)
	};


	sf::Clock clock;

	while (window.isOpen()) {
		//Pobiera czas, ktory uplynal od ostatniego wywolania clock.restart()
		sf::Time deltaTime = clock.restart();
		sf::Event event;

		//Nasluchiwnie zdarzen
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			// Ustawienie ekranu na rozdzielczosc 800x600 skrotem ALT+R
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

			// Obs³uga strza³ek na klawiaturze, które przesuwaj¹ nasz obiekt rect
			/*if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left) {
					rect.move(-5.f, 0.f);
					moveCounter++;
				}
				else if (event.key.code == sf::Keyboard::Right) {
					rect.move(5.f, 0.f);
					moveCounter++;
				}
				else if (event.key.code == sf::Keyboard::Up) {
					rect.move(0.f, -5.f);
					moveCounter++;
				}
				else if (event.key.code == sf::Keyboard::Down) {
					rect.move(0.f, 5.f);
					moveCounter++;
				}
			}*/

			// Ustawienie pelnego ekranu skrotem ALT+F (F-fullscreen)
			if (event.type == sf::Event::KeyPressed) {
				if ((event.key.code == sf::Keyboard::F) && (event.key.alt)) {
					setFullscreen(true);
				}
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					std::cout << "Pozycja myszy: " << mousePosition.x << ", " << mousePosition.y << std::endl;
					//std::cout << "Wcisnieto lewy przycisk myszy" << std::endl;
					//dalsza obsluga zdarzenia
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					std::cout << "Wcisnieto prawy przycisk myszy" << std::endl;
					//dalsza obsluga zdarzenia
				}
			}

		/*	if (event.type == sf::Event::MouseMoved) {
				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
				std::cout << "Pozycja myszy: " << mousePosition.x << ", " << mousePosition.y << std::endl;
			}*/

			if (moveCounter == 5)
			{
				// Losujemy nowy kolor
				bgColor = sf::Color(rand() % 256, rand() % 256, rand() % 256);
				// Resetujemy licznik ruchów
				moveCounter = 0;
			}



		}

		// Czyszczenie ekranu do zadanego koloru (np. jasnoniebieski)
		//window.clear(sf::Color(135, 206, 250));
		// Czyœcimy ekran do wylosowanego koloru
		window.clear(bgColor);

		// Wylczenie synchronizacji pionowej
		window.setVerticalSyncEnabled(true);

		newLine.drawLine(50, 40, 400, 100,window, sf::Color::Red);
		circle.drawCircle(300, 300, 100, window, sf::Color::Blue);
		rectangle.drawRectangle(vertices, window, sf::Color::Red);

		/* Nasz¹ scenê tworzymy wiêc na buforze, którego zawartoœæ jest automatycznie kopiowana na ekran w chwili wywo³ania metody display
		W SFML zarzadzanie technika wielokrotnego buforowania nastepuje automatycznie
		*/
		window.display();

		//std::cout << "Czas trwania klatki: " << deltaTime.asSeconds() << " sekundy" << std::endl;
	}
}


int main()
{
    Engine& engine = Engine::getInstance(800, 600, false);
    engine.setLimit(2);
    engine.run();

    return 0;
}